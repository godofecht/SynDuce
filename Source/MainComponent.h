#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/


class LetterDisplay : public Component
{
public:
    String LetterList[26];
    String letter_to_display = "";
    int letter_index = 0;
    Label letter_label;
    
    LetterDisplay()
    : LetterList{"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O","P","Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"}
    {
        
        addAndMakeVisible(letter_label);
        letter_label.setFont(80);
    }
    
    String getLetter(int i)
    {
        return(LetterList[i-1]);
    }
    
    void setLetter(int i)
    {
        letter_to_display = getLetter(i);
        letter_index = i;
        letter_label.setText(letter_to_display,dontSendNotification);

    }
    
    void resized()
    {
        letter_label.setBounds(getX() + 50,getY() + 50,80,80);
    }
    
    
};


class ColorPicker : public Component, public Button::Listener
{
public:
    OwnedArray<ShapeButton> sb;
    
    
    std::vector<std::vector<int>>* frequency;
    LetterDisplay* letterDisplay;
    
    //Setting rectangular pathing
    Path rec_path;
    
    Array<Colour> color_set = {Colours::red,Colours::blue,Colours::green,Colours::yellow,Colours::pink,Colours::orange,Colours::purple,Colours::grey,Colours::black};

    
    ColorPicker()
    {
        rec_path.addRectangle(0, 0, 20, 20);
        for(int i=0;i<8;i++)
        {
            ShapeButton *s = new ShapeButton("button"+String(i),color_set[i],Colours::white,Colours::white);
            addAndMakeVisible(s);
            s->addListener(this);
            sb.add(s);
        }
    }
    
    void setMainComponent(std::vector<std::vector<int>>* f,LetterDisplay* ld)
    {
        frequency = f;
        letterDisplay = ld;
    }
    
    void resized()
    {
        for(int i=0;i<8;i++)
        {
            sb[i]->setBounds(getWidth()*(i+1)/10,20,40,40);
            sb[i]->setShape(rec_path,true,true,true);
        }
    }
    
    void buttonClicked(Button* button)
    {
        for(int i=0;i<8;i++)
        {
            if(button == sb[i])
            {
                int letter_i = letterDisplay->letter_index;
                (*frequency)[letter_i][i] += 1;
            }
        }
    }
};




class MainComponent  : public juce::Component, public Timer
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void timerCallback() override;
    
    
    void EndTesting();

    ColorPicker c;
    LetterDisplay letterDisplay;
    
    
    TextButton startButton{"START"};
    
    
    int seconds_elapsed = 0;
    
    
    std::vector<std::vector<int>> frequency;
    
    
    
    void DisplayFrequencies(std::vector<int> f);
    
    std::vector<int> GenerateFrequencyArrayFromDist(std::vector<std::vector<int>> f);
private:
    

    
    //==============================================================================
    // Your private member variables go here...


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
