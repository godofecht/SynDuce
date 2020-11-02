#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);
    
    
    addAndMakeVisible(startButton);
    
    
    //initialize frequency vector here
    for(int i=0;i<26;i++)
    {
        std::vector<int> thisrow;
        for(int j=0;j<8;j++)
        {
            thisrow.push_back(0);
        }
        frequency.push_back(thisrow);
    }
    
    c.setMainComponent(&frequency,&letterDisplay);
    
    
    
    startButton.onClick = [&]
    {
        startTimer(1000);

        startButton.setVisible(false);
        
        addAndMakeVisible(c);
        addAndMakeVisible(letterDisplay);
        for(int i=0;i<8;i++)
        {
        //       addAndMakeVisible(c.sb[i]);
        }
           
           
        addAndMakeVisible(letterDisplay.letter_label);
        c.resized();
        letterDisplay.resized();
    };
}

MainComponent::~MainComponent()
{
}

void MainComponent::timerCallback()
{
    letterDisplay.setLetter(juce::Random::getSystemRandom().nextInt (24)+1);
    seconds_elapsed += 1;
    
    if(seconds_elapsed > 20)
    {
        stopTimer();
        EndTesting();
    }
    

    
}

void MainComponent::DisplayFrequencies(std::vector<int> f)
{
    for(int i=0;i<26;i++)
    {
        String s = letterDisplay.LetterList[i]+"->"+String(f[i]);
        DBG(s);
    }
}

std::vector<int> MainComponent::GenerateFrequencyArrayFromDist(std::vector<std::vector<int>> f)
{
    std::vector<int> fA;
    for(int letter_i=0;letter_i<26;letter_i++)
    {
        int maxIndex = 0;
        for(int color_i=0;color_i<8;color_i++)
        {
            if(f[letter_i][color_i] > f[letter_i][maxIndex])
            {
                maxIndex = color_i;
            }
        }
        fA.push_back(f[letter_i][maxIndex]);
    }
    
    return fA;
}

void MainComponent::EndTesting()
{
    c.setVisible(false);
    letterDisplay.setVisible(false);
    letterDisplay.letter_label.setVisible(false);
    
    
    std::vector<int> finalFreq;
    finalFreq = GenerateFrequencyArrayFromDist(frequency);
    DisplayFrequencies(finalFreq);
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont (juce::Font (16.0f));
    g.setColour (juce::Colours::white);
//    g.drawText ("Hello World!", getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized()
{
    startButton.setBounds(getWidth()/2 - 50,getHeight()/2,50,100);
    
    
    
    
    letterDisplay.setBounds(getWidth()/2 - 100,getHeight()/2,50,50);
    c.setBounds(0,0,getWidth(),getHeight()/2);
    
    c.resized();
    letterDisplay.resized();

    
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
