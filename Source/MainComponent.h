#pragma once

#include <JuceHeader.h>
#include <algorithm>
#include <vector>
#include <random>


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/


class ColorDisplay : public Component
{

public:
    //    String LetterList[26] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O","P","Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
    Colour color_to_display = Colour::fromRGB(0,0,0);
    int color_index = 0;

    Array<Colour> color_set{
    Colour::fromRGB(0, 0, 153),
    Colour::fromRGB(153, 51, 0),
    Colour::fromRGB(102, 255, 102),
    Colour::fromRGB(0, 128, 0),
    Colour::fromRGB(0, 204, 255),
    Colour::fromRGB(255, 161, 23),
    Colour::fromRGB(255, 0, 255),
    Colour::fromRGB(128, 0, 128),
    Colour::fromRGB(255, 0, 0),
    Colour::fromRGB(128, 128, 128),
    Colour::fromRGB(255, 255, 255),
    Colour::fromRGB(85, 85, 85),
    Colour::fromRGB(255, 255, 0),
    };

    //Setting rectangular pathing
    Path rec_path;

    ShapeButton* color_label;

    ColorDisplay()
        // :LetterList{"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O","P","Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"}

    {
        rec_path.addRectangle(0, 0, 20, 20);
        color_label = new ShapeButton("button" + String(0), color_set[0], Colours::white, Colours::white);

        addChildComponent(color_label);
        color_label->setVisible(true);

    }


    void SetColors(Array<Colour> cs)
    {
        color_set = cs;
    }

    Colour getColor(int i)
    {
        return(color_set[i - 1]);
    }

    void setColor(int i)
    {
        color_to_display = getColor(i);
        color_index = i;
        color_label->setColours(color_to_display, color_to_display, color_to_display);
    //    color_label.setText(color_to_display, dontSendNotification);

    }

    void resized() override
    {
        color_label->setBounds(getX() + 50, getY() + 50, 80, 80);
        color_label->setShape(rec_path, true, true, true);
    }



};
class LetterDisplay : public Component
{
public:
//    String LetterList[26] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O","P","Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
    std::vector<String> LetterList{ "b","d","e","g","i","o","p","q","r","u","w","x","y" };
    String letter_to_display = "";
    int letter_index = 0;

 

    Label letter_label;
    
    LetterDisplay()
   // :LetterList{"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O","P","Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"}
    
    {

        
        addChildComponent(letter_label);
        letter_label.setFont(80);

        letter_label.setVisible(true);
    }

    void SetLetters(std::vector<String> ll)
    {
        LetterList = ll;
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
    
    void resized() override
    {
        letter_label.setBounds(getX() + 50,getY() + 50,80,80);
    }  
};
class LetterPicker : public Component, public Button::Listener
{

public:
    std::vector<String> LetterList{ "b","d","e","g","i","o","p","q","r","u","w","x","y" };
    OwnedArray<TextButton
    > sb;

    int NUM_SQUARES = 13;


    std::vector<std::vector<int>>* frequency;
    LetterDisplay* letterDisplay;

    //Setting rectangular pathing
    Path rec_path;

    Array<Colour> color_set{
    Colour::fromRGB(0, 0, 153),
    Colour::fromRGB(153, 51, 0),
    Colour::fromRGB(102, 255, 102),
    Colour::fromRGB(0, 128, 0),
    Colour::fromRGB(0, 204, 255),
    Colour::fromRGB(255, 161, 23),
    Colour::fromRGB(255, 0, 255),
    Colour::fromRGB(128, 0, 128),
    Colour::fromRGB(255, 0, 0),
    Colour::fromRGB(128, 128, 128),
    Colour::fromRGB(255, 255, 255),
    Colour::fromRGB(85, 85, 85),
    Colour::fromRGB(255, 255, 0),
    };

    String testType;
    int sequence_counter = 0;
    int sequence_size = 0;
    std::vector<int> buttonSequence;


    bool bHasJustBeenClicked = false;


    LetterPicker()
    {
        rec_path.addRectangle(0, 0, 20, 20);
        for (int i = 0; i < NUM_SQUARES; i++)
        {
            TextButton* s = new TextButton("newbtn");
            s->setButtonText(LetterList[i]);
            this->addChildComponent(s);
            s->setVisible(true);
            s->addListener(this);
            sb.add(s);
        }

    }

    void setMainComponent(std::vector<std::vector<int>>* f, LetterDisplay* ld)
    {
        frequency = f;
        letterDisplay = ld;
    }

    void resized() override
    {
        for (int i = 0; i < NUM_SQUARES; i++)
        {
            sb[i]->setBounds(getParentWidth() * (i + 1) / (float)(NUM_SQUARES + 2), 20, 40, 40);
        //    sb[i]->setShape(rec_path, true, true, true);
        }
    }

    void buttonClicked(Button* button)
    {
        if (testType == "sequence")
        {
            if (sequence_counter < sequence_size)
            {
                for (int i = 0; i < sequence_size; i++)
                {
                    if (button == sb[i])
                        buttonSequence.push_back(i);
                }
                sequence_counter++;
            }
            button->setVisible(false);
        }
        else if (testType == "selection")
        {
            for (int i = 0; i < sequence_size; i++)
            {
                if (button == sb[i])
                {
                    int letter_i = letterDisplay->letter_index;
                    (*frequency)[letter_i][i] += 1;
                }
            }
            bHasJustBeenClicked = true;
        }
        else
        {
            for (int i = 0; i < sequence_size; i++)
            {
                if (button == sb[i])
                {
                    int letter_i = letterDisplay->letter_index;
                    (*frequency)[letter_i][i] += 1;
                }
            }
        }
    }


    void display()
    {
        this->setVisible(true);
    }

    void hide()
    {
        this->setVisible(false);
    }

    void Reset()
    {
    }
};
class ColorPicker : public Component, public Button::Listener
{
public:
    OwnedArray<ShapeButton> sb;

    int NUM_SQUARES;
    
    
    std::vector<std::vector<int>>* frequency;
    LetterDisplay* letterDisplay;
    
    //Setting rectangular pathing
    Path rec_path;
    
    Array<Colour> color_set{
    Colour::fromRGB(0, 0, 153),
    Colour::fromRGB(153, 51, 0),
    Colour::fromRGB(102, 255, 102),
    Colour::fromRGB(0, 128, 0),
    Colour::fromRGB(0, 204, 255),
    Colour::fromRGB(255, 161, 23),
    Colour::fromRGB(255, 0, 255),
    Colour::fromRGB(128, 0, 128),
    Colour::fromRGB(255, 0, 0),
    Colour::fromRGB(128, 128, 128),
    Colour::fromRGB(255, 255, 255),
    Colour::fromRGB(85, 85, 85),
    Colour::fromRGB(255, 255, 0),
    };

    String testType;
    int sequence_counter = 0;
    int sequence_size = 0;
    std::vector<int> buttonSequence;


    bool bHasJustBeenClicked = false;

    
    ColorPicker(int ns)
    {
        NUM_SQUARES = ns;
        rec_path.addRectangle(0, 0, 20, 20);
        for(int i=0;i<NUM_SQUARES;i++)
        {
            ShapeButton *s = new ShapeButton("button"+String(i),color_set[i],Colours::white,Colours::white);
            this->addChildComponent(s);
            s->setVisible(true);
            s->addListener(this);
            sb.add(s);
        }

    }
    
    void setMainComponent(std::vector<std::vector<int>>* f,LetterDisplay* ld)
    {
        frequency = f;
        letterDisplay = ld;
    }
    
    void resized() override
    {
        for(int i=0;i<NUM_SQUARES;i++)
        {
            sb[i]->setBounds(getParentWidth()*(i+1)/(float)(NUM_SQUARES + 2),20,40,40);
            sb[i]->setShape(rec_path,true,true,true);
        }
    }
    
    void buttonClicked(Button* button)
    {
        if (testType == "sequence")
        {
            if (sequence_counter < sequence_size)
            {
                for (int i = 0; i < sequence_size; i++)
                {
                    if (button == sb[i])
                        buttonSequence.push_back(i);
                }
                sequence_counter++;
            }
            button->setVisible(false);
        }
        else if (testType == "selection")
        {
            for (int i = 0; i < sequence_size; i++)
            {
                if (button == sb[i])
                {
                    int letter_i = letterDisplay->letter_index;
                    (*frequency)[letter_i][i] += 1;
                }
            }
            bHasJustBeenClicked = true;
        }
        else
        {
            for (int i = 0; i < sequence_size; i++)
            {
                if (button == sb[i])
                {
                    int letter_i = letterDisplay->letter_index;
                    (*frequency)[letter_i][i] += 1;
                }
            }
        }
    }


    void display()
    {
        this->setVisible(true);
    }

    void hide()
    {
        this->setVisible(false);
    }

    void Refresh()
    {
        for (int i = 0; i < NUM_SQUARES; i++)
        {
            sb[i]->setColours(color_set[i], color_set[i],color_set[i]);
        }
    }
};

class PassiveDrill : public juce::Component
{
public:


    std::vector<String> LetterList{ "b","d","e","g","i","o","p","q","r","u","w","x","y" };
    std::vector<Colour> colorList{
        Colour::fromRGB(0, 0, 153),
        Colour::fromRGB(153, 51, 0),
        Colour::fromRGB(102, 255, 102),
        Colour::fromRGB(0, 128, 0),
        Colour::fromRGB(0, 204, 255),
        Colour::fromRGB(255, 161, 23),
        Colour::fromRGB(255, 0, 255),
        Colour::fromRGB(128, 0, 128),
        Colour::fromRGB(255, 0, 0),
        Colour::fromRGB(128, 128, 128),
        Colour::fromRGB(255, 255, 255),
        Colour::fromRGB(85, 85, 85),
        Colour::fromRGB(255, 255, 0),
    };

    bool bBlackLetters = false;

    bool bStopTimer = false;
    int duration =  4 * 60 * 60;
    int time_per_letter = 500;
    int time_elapsed_since_last_letter = 0;
    int time_between_letters = 0;
    bool b_letter_just_displayed = false;

    std::vector<std::vector<int>> frequency;

    LetterDisplay ld;

    double seconds_elapsed = 0;

    Colour getColor(int letter_i)
    {
        return colorList[letter_i];
    }

    std::vector<String> getLetterList()
    {
        return LetterList;
    }

    PassiveDrill()
    {
        addChildComponent(ld);

        ld.SetLetters(LetterList);
        InitializeFrequencyVector();






        ld.setVisible(true);
        ld.setBounds(0, 0, getParentWidth(), getParentHeight());
    }

    void OnSelect()
    {

    }

    void InitializeFrequencyVector()
    {
        //initialize frequency vector here
        for (int i = 0; i < LetterList.size(); i++)
        {
            std::vector<int> thisrow;
            for (int j = 0; j < 13; j++)
            {
                thisrow.push_back(0);
            }
            frequency.push_back(thisrow);
        }
    }

    void timed()
    {
        if (!bStopTimer) //if timer is running
        {
            time_elapsed_since_last_letter += 100; // 100 is the timer value from startTimer(1000);
            if (time_elapsed_since_last_letter > time_per_letter)
            {
                ld.letter_label.setText(" ", dontSendNotification);
            }
            //If letter not just displayed
            if (time_elapsed_since_last_letter > time_per_letter + time_between_letters)
            {
                //reset letter display timer
                time_elapsed_since_last_letter = 0;

                //Display letter
                int letter_index = juce::Random::getSystemRandom().nextInt(LetterList.size() - 2) + 1;
                ld.setLetter(letter_index);
                if(!bBlackLetters)
                    ld.letter_label.setColour(juce::Label::textColourId, getColor(letter_index));
                else
                {
                    ld.letter_label.setColour(juce::Label::textColourId, Colours::black);

                }
                //Progress timer since we're moving forward through time
                seconds_elapsed += 100;

                b_letter_just_displayed = true;
            }
            // if time's up
            if (seconds_elapsed > duration)
            {
                bStopTimer = true;
                EndTest();
            }
        }

        //If is in refractory cycle (blank in between letters)

    }

    void resized() override
    {
        ld.resized();
    }

    void EndTest()
    {
      ld.setVisible(false);
      this->setVisible(false);
      ld.letter_label.setVisible(false);


      std::vector<int> finalFreq;
      finalFreq = GenerateFrequencyArrayFromDist(frequency);
      DisplayFrequencies(finalFreq);
    }

    std::vector<int> GenerateFrequencyArrayFromDist(std::vector<std::vector<int>> f)
    {
        std::vector<int> fA;
        for (int letter_i = 0; letter_i < 26; letter_i++)
        {
            int maxIndex = 0;
            for (int color_i = 0; color_i < 13; color_i++)
            {
                if (f[letter_i][color_i] > f[letter_i][maxIndex])
                {
                    maxIndex = color_i;
                }
            }
            fA.push_back(f[letter_i][maxIndex]);
        }

        return fA;
    }

    void DisplayFrequencies(std::vector<int> f)
    {
        for(int i=0;i<26;i++)
        {
            String s = ld.LetterList[i]+"->"+String(f[i]);
            DBG(s);
        }
    }
};

class EarlySpan : public PassiveDrill
{
public:

    ColorPicker* c;
    int sequenceCounter = 1;

    EarlySpan()
    {
        c = new ColorPicker(13);

        addChildComponent(ld);
        addChildComponent(c);

        time_per_letter = 100; //fine-tune these values according to paper
        time_between_letters = 0;
        ld.SetLetters(getLetterList());
        c->setMainComponent(&frequency, &ld);
        GetRandomLetterSequence();

        ld.setVisible(true);

        duration = 100 * 13 + time_between_letters * 13;

        DisplayMessage("Respond");

        c->testType = "sequence";
        c->sequence_size = 13;

        

    }

    void resized() override
    {
        setBounds(0, 0, getParentWidth(), getParentHeight());
        ld.setBounds(0, 0, getParentWidth(), getParentHeight());
        c->setBounds(0, 0, getParentWidth(), getParentHeight());
        ld.resized();
        c->resized();
    }

    std::vector<String> GetRandomLetterSequence()
    {
        auto rd = std::random_device{};
        auto rng = std::default_random_engine{ rd() };

        std::vector<String> tempVector = getLetterList();
        std::shuffle(ld.LetterList.begin(), ld.LetterList.end(), rng);

        return tempVector;
    }

    void timed()
    {


        //if test over
        if (seconds_elapsed >= duration)
        {

            c->setVisible(true);
        }

        else
        {
            //Progress timer since we're moving forward through time
            seconds_elapsed += 100;
       //     DBG(LetterList.size());
            if (!bStopTimer && sequenceCounter < 12) //if timer is running
            {
                time_elapsed_since_last_letter += 100; // 100 is the timer value from startTimer(1000);
                if (time_elapsed_since_last_letter > time_per_letter)
                {
                    ld.letter_label.setText(" ", dontSendNotification);
                }
                //If letter not just displayed
                if (time_elapsed_since_last_letter > time_per_letter + time_between_letters)
                {
                    //reset letter display timer
                    time_elapsed_since_last_letter = 0;

                    //Display letter
                    int letter_index = sequenceCounter; sequenceCounter++;

                    ld.SetLetters(LetterList);
                    ld.setLetter(letter_index);
                    if (!bBlackLetters)
                        ld.letter_label.setColour(juce::Label::textColourId, getColor(letter_index));
                    else
                    {
                        ld.letter_label.setColour(juce::Label::textColourId, Colours::black);

                    }



                    b_letter_just_displayed = true;
                }
                // if time's up
                if (seconds_elapsed > duration)
                {
                    bStopTimer = true;
                    EndTest();
                }
            }
            
        }
    }

    void DisplayMessage(String s)
    {
        //convert this console message to an on screen message
        DBG(s);
    }
};

class LateSpan : public EarlySpan
{
public:

    LetterPicker c;
    ColorDisplay ld;

    std::vector<String> LetterList{ "b","d","e","g","i","o","p","q","r","u","w","x","y" };
    Array<Colour> color_set{
    Colour::fromRGB(0, 0, 153),
    Colour::fromRGB(153, 51, 0),
    Colour::fromRGB(102, 255, 102),
    Colour::fromRGB(0, 128, 0),
    Colour::fromRGB(0, 204, 255),
    Colour::fromRGB(255, 161, 23),
    Colour::fromRGB(255, 0, 255),
    Colour::fromRGB(128, 0, 128),
    Colour::fromRGB(255, 0, 0),
    Colour::fromRGB(128, 128, 128),
    Colour::fromRGB(255, 255, 255),
    Colour::fromRGB(85, 85, 85),
    Colour::fromRGB(255, 255, 0),
    };


    LateSpan()
    {
        addChildComponent(ld);
        addChildComponent(c);




        time_per_letter = 100;
        time_between_letters = 0;
        ld.SetColors(color_set);
 //       c.setMainComponent(&frequency, &ld);


        ld.setVisible(true);

        duration = 100;

        DisplayMessage("Respond");

        c.testType = "sequence";
        c.sequence_size = 13;

    }

    Colour getColor(int letter_i)
    {
        return colorList[letter_i];
    }

    void resized() override
    {
        setBounds(0, 0, getParentWidth(), getParentHeight());

        ld.setBounds(0, 0, getParentWidth(), getParentHeight());

        c.setBounds(0, 0, getParentWidth(), getParentHeight());


        ld.resized();
        c.resized();
    }

    void timed()
    {


        //if test over
        if (seconds_elapsed >= duration)
        {
            c.setVisible(true);
        }
        else
        {


            if (!bStopTimer) //if timer is running
            {
                //If timer's on, move forward through time
                time_elapsed_since_last_letter += 100; // 100 is the timer value from startTimer(1000);

                //if letter displayed
          //      if (b_letter_just_displayed)
          //      {
                if (time_elapsed_since_last_letter > time_per_letter)
                {
                    //   time_elapsed_since_last_letter = 0;
                    //   ld.color_label->setText(" ", dontSendNotification);
         //              b_letter_just_displayed = false;
                }
                //       }
                       //If letter not just displayed
                if (time_elapsed_since_last_letter > time_per_letter + time_between_letters)
                {
                    //reset letter display timer
                    time_elapsed_since_last_letter = 0;

                    //Display letter
                    int letter_index = juce::Random::getSystemRandom().nextInt(ld.color_set.size() - 2) + 1;
                    DBG(letter_index);
                    repaint();
                    ld.setColor(letter_index);
                    //Progress timer since we're moving forward through time
                    seconds_elapsed += 100;

                    b_letter_just_displayed = true;

                    DBG("done");
                }
                // if time's up
                if (seconds_elapsed > duration)
                {
                    bStopTimer = true;
                    //        EndTest();
                }
            }

            //If is in refractory cycle (blank in between letters)
        }
    }

    void DisplayMessage(String s)
    {
        //convert this console message to an on screen message
        DBG(s);
    }
};

class BackwardSpan : public EarlySpan
{

};

class AdvancedSpan : public EarlySpan
{
public:



    AdvancedSpan()
    {
        addChildComponent(ld);
        addChildComponent(c);
        time_per_letter = 1000;
        time_between_letters = 250;
        ld.SetLetters(getLetterList());
        bBlackLetters = true;
        ld.setVisible(true);
        duration = 100;
    }
};



class EDMTS : public juce::Component
{
public:
    bool bBlackLetters = false;
    std::vector<String> LetterList{ "b","d","e","g","i","o","p","q","r","u","w","x","y" };
    std::vector<Colour> colorList{
        Colour::fromRGB(0, 0, 153),
        Colour::fromRGB(153, 51, 0),
        Colour::fromRGB(102, 255, 102),
        Colour::fromRGB(0, 128, 0),
        Colour::fromRGB(0, 204, 255),
        Colour::fromRGB(255, 161, 23),
        Colour::fromRGB(255, 0, 255),
        Colour::fromRGB(128, 0, 128),
        Colour::fromRGB(255, 0, 0),
        Colour::fromRGB(128, 128, 128),
        Colour::fromRGB(255, 255, 255),
        Colour::fromRGB(85, 85, 85),
        Colour::fromRGB(255, 255, 0),
    };

    LetterDisplay ld;
    std::vector<std::vector<int>> frequency;

    bool bStopTimer = false;
    int duration = 4 * 60 * 60;
    int time_per_letter = 1500;
    int time_elapsed_since_last_letter = 0;
    int time_between_letters = 0;
    int time_between_letter_and_colors = 3000;
    int time_for_selection = 4000;
    bool b_letter_just_displayed = false;

    double seconds_elapsed = 0;

    bool b_just_started = false;

    ColorPicker* cp;

    Colour getColor(int letter_i)
    {
        return colorList[letter_i];
    }

    std::vector<String> getLetterList()
    {
        return LetterList;
    }

    void InitializeFrequencyVector()
    {
        //initialize frequency vector here
        for (int i = 0; i < LetterList.size(); i++)
        {
            std::vector<int> thisrow;
            for (int j = 0; j < 13; j++)
            {
                thisrow.push_back(0);
            }
            frequency.push_back(thisrow);
        }
    }

    EDMTS()
    {

        cp = new ColorPicker(2);

        cp->testType = "selection";
        cp->sequence_size = 2;

        addChildComponent(ld);
        addChildComponent(cp);

        cp->color_set.clear();
        cp->color_set.add(Colours::green);
        cp->color_set.add(Colours::blue);
        cp->NUM_SQUARES = 2;

        cp->setMainComponent(&frequency, &ld);

        ld.SetLetters(LetterList);
        InitializeFrequencyVector();




        ld.setVisible(true);
        ld.setBounds(0, 0, getParentWidth(), getParentHeight());
        cp->setBounds(30, 30, 50, 50);




    }

    void GenerateNextLetterTest()
    {








        //reset letter display timer
        time_elapsed_since_last_letter = 0;
        //Display letter
        int letter_index = juce::Random::getSystemRandom().nextInt(LetterList.size() - 2) + 1;
        ld.setLetter(letter_index);
        if (!bBlackLetters)
            ld.letter_label.setColour(juce::Label::textColourId, getColor(letter_index));
        else
        {
            ld.letter_label.setColour(juce::Label::textColourId, Colours::black);
        }


        cp->color_set.clear();
        cp->color_set.add(colorList[letter_index]);
        cp->color_set.add(getColor(letter_index % cp->NUM_SQUARES));
        cp->NUM_SQUARES = 2;
        cp->Refresh();
        repaint();
    }

    void start()
    {
        b_just_started = true;
    }

    void timed()
    {
        if (!bStopTimer) //if timer is running
        {
            time_elapsed_since_last_letter += 100; // 100 is the timer value from startTimer(1000);
            if (time_elapsed_since_last_letter > time_per_letter) 
            {
                ld.letter_label.setText(" ", dontSendNotification);
            }
            //If letter not just displayed
            if (time_elapsed_since_last_letter > time_per_letter + time_between_letters)
            {
                cp->setVisible(true);
               



                //Progress timer since we're moving forward through time
                seconds_elapsed += 100;

                b_letter_just_displayed = true;




            }

            if (cp->bHasJustBeenClicked || time_elapsed_since_last_letter > time_per_letter + time_between_letters + time_for_selection || b_just_started)
            {
                b_just_started = false;
                cp->setVisible(false);
                cp->bHasJustBeenClicked = false;
                GenerateNextLetterTest();
            }

            // if time's up
            if (seconds_elapsed > duration)
            {
                OnDurationEnd();
            }
        }

        //If is in refractory cycle (blank in between letters)

    }

    void OnDurationEnd()
    {
        bStopTimer = true;
        EndTest();
    }

    void EndTest()
    {
        ld.setVisible(false);
        this->setVisible(false);
        ld.letter_label.setVisible(false);


        std::vector<int> finalFreq;
        finalFreq = GenerateFrequencyArrayFromDist(frequency);
        DisplayFrequencies(finalFreq);
    }

    void resized() override
    {
        setBounds(0, 0, getParentWidth(), getParentHeight());
        ld.setBounds(0, 0, getParentWidth(), getParentHeight());
        cp->setBounds(0, 0, getParentWidth(), getParentHeight());
        ld.resized();
        cp->resized();
    }


    std::vector<int> GenerateFrequencyArrayFromDist(std::vector<std::vector<int>> f)
    {
        std::vector<int> fA;
        for (int letter_i = 0; letter_i < 26; letter_i++)
        {
            int maxIndex = 0;
            for (int color_i = 0; color_i < 13; color_i++)
            {
                if (f[letter_i][color_i] > f[letter_i][maxIndex])
                {
                    maxIndex = color_i;
                }
            }
            fA.push_back(f[letter_i][maxIndex]);
        }

        return fA;
    }

    void DisplayFrequencies(std::vector<int> f)
    {
        for (int i = 0; i < 26; i++)
        {
            String s = ld.LetterList[i] + "->" + String(f[i]);
            DBG(s);
        }
    }
};

class LDMTS : public EDMTS
{
public:


    LDMTS()
    {
        bBlackLetters = true;
    }
};


class LCST : public EarlySpan
{
public:
    LCST()
    {
        bBlackLetters = true;

        addChildComponent(ld);
        addChildComponent(c);

        time_per_letter = 1000;
        time_between_letters = 0;
        ld.SetLetters(getLetterList());
        c->setMainComponent(&frequency, &ld);


        ld.setVisible(true);


        duration = 1000;

        DisplayMessage("Respond");

        c->sequence_size = 13;
        c->testType = "selection";
        c->setVisible(true);

    }

    void resized() override
    {
        c->setBounds(0, getParentHeight() - 100.0f, getParentWidth(), 100.0f);
    }

    void timed()
    {
        if (c->bHasJustBeenClicked)
        {
            OnSelect();
            c->bHasJustBeenClicked = false;
        }
    }

    void OnSelect()
    {
        //Display letter
        int letter_index = juce::Random::getSystemRandom().nextInt(LetterList.size() - 2) + 1;
        ld.setLetter(letter_index);

        if (!bBlackLetters)
            ld.letter_label.setColour(juce::Label::textColourId, getColor(letter_index));
        else
        {
            ld.letter_label.setColour(juce::Label::textColourId, Colours::black);

        }
    }
};


class CLST : public Component
{
public:
    LetterPicker lp;


    bool bStopTimer = false;

    int duration = 4 * 60 * 60;

    int time_per_letter = 500;
    int time_elapsed_since_last_letter = 0;
    int time_between_letters = 0;
    bool b_letter_just_displayed = false;

    std::vector<std::vector<int>> frequency;

    ColorDisplay ld;

    double seconds_elapsed = 0;


    CLST()
    {

        addAndMakeVisible(lp);
        addAndMakeVisible(ld);


        time_per_letter = 100;
        time_between_letters = 250;
   //     cd.SetLetters(getLetterList());
   //     c.setMainComponent(&frequency, &ld);




        lp.setVisible(true);


        ld.setVisible(true);







        lp.testType = "sequence";
        lp.sequence_size = 13;
    }

    void resized()
    {
        setBounds(0, 0, getParentWidth(), getParentHeight());
        lp.setBounds(0, getParentHeight()*7.0f/10.0f, getParentWidth(), getParentHeight());
        ld.setBounds(0, 0, getParentWidth(), getParentHeight());
        lp.resized();
        ld.resized();
    }


    void timed()
    {


        if (!bStopTimer) //if timer is running
        {
            //If timer's on, move forward through time
            time_elapsed_since_last_letter += 100; // 100 is the timer value from startTimer(1000);
            
            //if letter displayed
      //      if (b_letter_just_displayed)
      //      {
                if (time_elapsed_since_last_letter > time_per_letter)
                {
                 //   time_elapsed_since_last_letter = 0;
                 //   ld.color_label->setText(" ", dontSendNotification);
      //              b_letter_just_displayed = false;
                }
     //       }
            //If letter not just displayed
            if (time_elapsed_since_last_letter > time_per_letter + time_between_letters)
            {
                    //reset letter display timer
                    time_elapsed_since_last_letter = 0;

                    //Display letter
                    int letter_index = juce::Random::getSystemRandom().nextInt(ld.color_set.size() - 2) + 1;
                    DBG(letter_index);
                    repaint();
                    ld.setColor(letter_index);
                    //Progress timer since we're moving forward through time
                    seconds_elapsed += 100;

                    b_letter_just_displayed = true;

                    DBG("done");
            }
            // if time's up
            if (seconds_elapsed > duration)
            {
                bStopTimer = true;
        //        EndTest();
            }
        }

        //If is in refractory cycle (blank in between letters)
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



    LDMTS ls;


 //   ColorPicker c;
 //   LetterDisplay letterDisplay;
    
    
    TextButton startButton{"START"};
    
    
    int seconds_elapsed = 0;
    
    

    
    
    
  
private:
    

    
    //==============================================================================
    // Your private member variables go here...


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};




