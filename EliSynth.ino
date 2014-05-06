#define C4 60

#define DEFAULT_ARPEGGIO_CAPACITY 4

/* an Arpeggio is a series of notes played in a rhythm specified by one or more ArpeggioElements.
 * an ArpeggioElement specifies a note's start relative to the beginning of a Sequence and duration in beats.
 * an Arpeggio is triggered with one or more notes which are bound to the ArpeggioElements to create a series of MIDI events.
 
 * a Melody is a series of notes whose tone and rhythm are specified by MelodyElements.
 * a MelodyEvent is an ArpeggioEvent plus a tone; tones in a Melody are relative offsets from the first tone in the Melody.
 * a Melody is triggered with a single base tone that is used to render the MelodyElements to MIDI events.
*/

class ArpeggioElement
{
  float start;    // relative to start of Arpeggio in beats, must be >= 0
  float duration; // relative to start of note in beats, must be >= 0
  
  public:
  ArpeggioElement(float s, float d)
  {
    if (s < 0)
    {
      Serial.print ("note start < 0: reassigned to 0");
      s = 0;
    }
    
    start = s;
    
    if (d < 0)
    {
      Serial.print ("note duration < 0: reassigned to 0");
      d = 0;
    }
    duration = d;
  }
  
  ArpeggioElement()
  {
    start = 0;
    duration = 0;
  }
};

class Arpeggio
{
  ArpeggioElement *durations;
  
  public: 
  int length;
  int capacity;
  
  Arpeggio ()
  {
    length = 0;
    durations = new ArpeggioElement[DEFAULT_ARPEGGIO_CAPACITY];
  }
  
  Arpeggio (ArpeggioElement d[], int l)
  {
    durations = d;
    length = l;
    capacity = l;
  }
 
  void add(ArpeggioElement nd)
  {
    if (length == capacity)
    {
      ArpeggioElement *oldND = durations;
      ArpeggioElement *newND = new ArpeggioElement[capacity * 2];
      int i;
      
      for (i = 0; i < length; i++)
      {
        newND[i] = durations[i];
      }
      
      durations = newND;
      durations[i + 1] = nd;
      length++;
      capacity *= 2;
      
      free (oldND);
    }
  }
};

void Midi_Send(byte cmd, byte data1, byte data2) 
{
  Serial.write(cmd);
  Serial.write(data1);
  Serial.write(data2);
}

void setup()
{
}

void loop()
{
}


