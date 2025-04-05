import speech_recognition as sr
import pyttsx3
import spacy
from nltk.sentiment.vader import SentimentIntensityAnalyzer
from TTS.api import TTS
import sounddevice as sd
import nltk
# Define the colors to be recognized
colors = ["red", "blue", "green", "yellow", "black", "white", "orange", "purple", "pink", "brown", "gray"]
#positive_keywords = ['yes', 'yeah', 'yep', 'sure', 'definitely', 'absolutely', 'affirmative']
#negative_keywords = ['no', 'nope', 'nah', 'negative', 'not', 'never', 'absolutely not']

def extract_action_color_object(doc):
    # Process the text with spaCy
    extracted_data = {
        "do": [],
        "don't": []
    }
    current_colors = []
    is_negated = False
    action = None
    for token in doc:
        # Detect the main verb (action)
        if token.dep_ == "ROOT":
            action = token.text
        # Detect negation
        if token.dep_ == "neg":
            is_negated = True
        if token.text.lower() in colors:
            current_colors.append(token.text)
        elif token.dep_ in ("pobj", "dobj") and current_colors:
            action_type = "don't" if is_negated else "do"
            for color in current_colors:
                extracted_data[action_type].append({"action": action, "color": color, "object": token.text})
            current_colors = []  # Reset after finding objects
            is_negated = False  # Reset negation after handling the object
        elif token.text.lower() == "or":
            continue  # Keep adding colors until object is found
    return extracted_data


class SpeechResult:
    def __init__(self, text: str, nlp) -> None:
        self.text = text
        self.doc = nlp(text)
        nltk.download('vader_lexicon')
        self.sia = SentimentIntensityAnalyzer()
    
    def color(self) -> list[str]:
        obj = extract_action_color_object(self.doc)
        colors = []
        for act in obj["do"]:
            colors.append(act["color"])
        return colors
    
    def is_yes(self):
        text = self.text
        sentiment_scores = self.sia.polarity_scores(text)
        compound_score = sentiment_scores['compound']
        if compound_score >= 0.05:
            return True
        elif compound_score <= -0.05:
            return False
        else:
            return False
    
    def get_parking_instruction(self) -> dict:
        
        sentance = self.doc
        print(sentance)
        is_negated = any(token.dep_ == "neg" for token in sentance)
        colors_found = [token.text.lower() for token in sentance if token.text.lower() in colors]
        location = " ".join([token.text for token in sentance if token.dep_ == "pobj"])
        verb = [token.text for token in sentance if token.pos_ == "VERB"]
        print(is_negated, colors_found, location, verb)
        if colors_found and location:
            return {"is_negated": is_negated, "color": colors_found[0], "location": location}
        return None
    
    def text(self) -> str:
        return self.text
        

class Speech:
    def __init__(self, nosr = False) -> None:
        self.r = sr.Recognizer()
        #self.engine = pyttsx3.init("espeak")
        self.nlp = spacy.load("en_core_web_sm")
        # no speech recognition, kbd only
        self.nosr = nosr
        
        self.tts = TTS(model_name="tts_models/en/ljspeech/tacotron2-DDC")
    
    def recognize_voice(self) -> SpeechResult:
        with sr.Microphone() as source:
            self.r.adjust_for_ambient_noise(source, duration=1)  # Adjust for ambient noise
            print("Speak something...")
            audio_data = self.r.listen(source, timeout=5)  # Timeout after 5 seconds
            print("Recognizing...")
            try:
                text = self.r.recognize_google(audio_data)
                print(f"You said: {text}")
                return SpeechResult(text, self.nlp)
            except sr.UnknownValueError as e:
                print("Sorry, I could not understand the audio")
                raise e
            except sr.RequestError as e:
                print("Could not request results; check your network connection")
                raise e
    
    def recognize(self) -> SpeechResult:
        if self.nosr:
            return SpeechResult(input("[write your instructions]:"), self.nlp)
        try:
            return self.recognize_voice()
        except:
            return SpeechResult(input("[write your instructions]:"), self.nlp)

    def speak(self, text):
        print(f"[ROBOT] {text}")
        #self.engine.setProperty('rate', 150)
        #self.engine.setProperty('volume', 0.9)
        #self.engine.say(text)
        #self.engine.runAndWait()
        
        wav = self.tts.tts(text)
        # Get the sample rate of the generated audio
        sample_rate = self.tts.synthesizer.output_sample_rate
        # Play the audio using sounddevice
        sd.play(wav, samplerate=sample_rate)
        sd.wait() 
