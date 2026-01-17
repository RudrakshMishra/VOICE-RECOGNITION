"""
Audio Data Collection Script for Edge Impulse
Collects voice samples and uploads to Edge Impulse Studio

Requirements:
pip install edge-impulse-linux
pip install pyaudio
pip install numpy
"""

import pyaudio
import wave
import numpy as np
import json
import os
from datetime import datetime

# Configuration
SAMPLE_RATE = 16000
CHANNELS = 1
CHUNK = 1024
RECORD_SECONDS = 1
OUTPUT_DIR = "audio_samples"

# Voice commands to collect
COMMANDS = ["yes", "no", "up", "down", "left", "right", "on", "off"]

class AudioCollector:
    def __init__(self):
        self.audio = pyaudio.PyAudio()
        if not os.path.exists(OUTPUT_DIR):
            os.makedirs(OUTPUT_DIR)
    
    def record_sample(self, label, sample_num):
        """Record a single audio sample"""
        print(f"\nRecording '{label}' - Sample {sample_num}")
        print("Say the word now...")
        
        stream = self.audio.open(
            format=pyaudio.paInt16,
            channels=CHANNELS,
            rate=SAMPLE_RATE,
            input=True,
            frames_per_buffer=CHUNK
        )
        
        frames = []
        
        for i in range(0, int(SAMPLE_RATE / CHUNK * RECORD_SECONDS)):
            data = stream.read(CHUNK)
            frames.append(data)
        
        stream.stop_stream()
        stream.close()
        
        # Save the recording
        filename = f"{OUTPUT_DIR}/{label}_{sample_num}_{datetime.now().strftime('%Y%m%d_%H%M%S')}.wav"
        wf = wave.open(filename, 'wb')
        wf.setnchannels(CHANNELS)
        wf.setsampwidth(self.audio.get_sample_size(pyaudio.paInt16))
        wf.setframerate(SAMPLE_RATE)
        wf.writeframes(b''.join(frames))
        wf.close()
        
        print(f"Saved: {filename}")
        return filename
    
    def collect_dataset(self, samples_per_label=10):
        """Collect dataset for all commands"""
        print("=== Voice Command Data Collection ===")
        print(f"Sample rate: {SAMPLE_RATE} Hz")
        print(f"Duration: {RECORD_SECONDS} second(s) per sample")
        print(f"Samples per command: {samples_per_label}")
        print(f"\nCommands: {', '.join(COMMANDS)}\n")
        
        for command in COMMANDS:
            print(f"\n--- Collecting samples for: {command.upper()} ---")
            for i in range(samples_per_label):
                input(f"Press Enter to record sample {i+1}/{samples_per_label}...")
                self.record_sample(command, i+1)
        
        print("\n=== Data collection complete! ===")
        print(f"All samples saved to: {OUTPUT_DIR}/")
        print("\nNext steps:")
        print("1. Upload samples to Edge Impulse Studio")
        print("2. Design your impulse (Audio MFCC -> Neural Network)")
        print("3. Train the model")
        print("4. Deploy to ESP32")
    
    def close(self):
        """Clean up resources"""
        self.audio.terminate()

def create_metadata_file():
    """Create a metadata file for Edge Impulse"""
    metadata = {
        "version": 1,
        "name": "Voice Commands Dataset",
        "description": "Custom voice command dataset",
        "sampleRate": SAMPLE_RATE,
        "channels": CHANNELS,
        "labels": COMMANDS,
        "samplesPerLabel": 10,
        "duration": RECORD_SECONDS
    }
    
    with open(f"{OUTPUT_DIR}/metadata.json", 'w') as f:
        json.dump(metadata, f, indent=2)
    
    print(f"Metadata saved to {OUTPUT_DIR}/metadata.json")

if __name__ == "__main__":
    collector = AudioCollector()
    
    try:
        collector.collect_dataset(samples_per_label=10)
        create_metadata_file()
    except KeyboardInterrupt:
        print("\n\nData collection interrupted by user")
    finally:
        collector.close()
