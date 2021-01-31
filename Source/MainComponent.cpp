#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    addChildComponent(startButton);
    addChildComponent(ls);
    startButton.setVisible(true);
    

    
    


    startButton.onClick = [&]
    {
        startTimer(100);
        startButton.setVisible(false);     
        ls.setVisible(true);
        ls.start();
    };




    setSize(600, 400);
}

MainComponent::~MainComponent()
{
}

void MainComponent::timerCallback()
{    
    ls.timed();
}





void MainComponent::EndTesting()
{

}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
   
    //fill this with opaque beige.
 //   g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.fillAll(Colour(196, 188, 150));

    g.setFont (juce::Font (16.0f));
    g.setColour (juce::Colours::white);
//    g.drawText ("Hello World!", getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized()
{


    startButton.setBounds(getWidth()/2 - 50,getHeight()/2,50,100);

    ls.setBounds(0, 0, getWidth(), getHeight());
    ls.resized();
    
    

    
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
