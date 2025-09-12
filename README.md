# VOICE-RECOGNITION
Real-time Voice Recognition using Edge Impulse &amp; ESP32. Captures audio via MEMS microphone, processes it with ML models, and recognizes commands for smart assistants, security, accessibility, and IoT applications.# 🎙️ Voice Recognition Project

This project demonstrates **real-time voice recognition** using an **ESP32 + INMP441 MEMS microphone** and **Edge Impulse**. The system captures audio, processes it with machine learning models, and recognizes spoken commands in real time.  

---

## 🚀 Features
- Captures audio through the INMP441 MEMS microphone.  
- Uses **Edge Impulse** to train ML models on voice commands.  
- Deploys firmware on ESP32 for **low-power, real-time recognition**.  
- Supports smart home control, accessibility, and IoT applications.  

---

## 🔧 Workflow
1. **Data Acquisition**  
   - Use a pre-made dataset or record audio samples.  
   - Each sample is 1 second long.  

2. **Impulse Design**  
   - Add **Time Series Data → Audio (MFCC) → Classification (Keras)** block.  
   - Window size = 1 second.  

3. **Feature Extraction**  
   - Configure MFCC block.  
   - Use autotune parameters and generate features.  

4. **Model Training**  
   - Configure the Neural Network classifier.  
   - Train for 50 cycles.  

5. **Testing**  
   - Upload test audio samples.  
   - Use **Model Testing → Classify selected** to view results.  

6. **Deployment**  
   - Add deployment code in Arduino IDE.  
   - Flash firmware on ESP32.  
   - Run model → recognized words/commands are displayed in **Serial Monitor**.  

---

## 🌍 Real-World Applications
- 🗣️ **Virtual Assistants** – Powering Alexa, Siri, Google Assistant alternatives.  
- 🔒 **Security** – Voice biometrics for authentication in banking & secure systems.  
- 📞 **Customer Service** – Call routing & automation in call centers.  
- 🌍 **Translation** – Real-time speech-to-speech translation.  
- ♿ **Accessibility** – Hands-free device control & live captioning.  

---

## 📂 Repository Structure

