using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Windows.Forms;

namespace Project1_Gangemi
{
    public partial class form1 : Form
    {
        #region Globals
        static char[] alphabet = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'Y', 'X', 'Z' };
        static Random rnd = new Random();
        List<string> words = new List<string>(); // stores possible selection of words
        List<Button> controls = new List<Button>(); // stores user selectable controls
        #endregion

        public form1()
        {
            InitializeComponent();
            InitializeWords();
            InitializeListbBox();
            InitializeControls();
            ResetControls();
        }

        #region Utility Methods
        /// <summary>
        /// Initializes the list |words| from Words5.txt
        /// </summary>
        private void InitializeWords()
        {
            StreamReader reader = new StreamReader("Words5.txt");
            
            while(!reader.EndOfStream)
                words.Add(reader.ReadLine().Trim());

            reader.Close();
        }

        /// <summary>
        /// Initializes the list |controls| with buttons on the form
        /// </summary>
        private void InitializeControls()
        {
            controls.Add(button1);
            controls.Add(button2);
            controls.Add(button3);
            controls.Add(button4);
            controls.Add(button5);
        }

        /// <summary>
        /// Initializes the list box with |words| list
        /// </summary>
        private void InitializeListbBox()
        {
            listboxWords.Items.Clear();
            listboxWords.Items.AddRange(words.ToArray());
        }

        /// <summary>
        /// Reset all controls
        /// </summary>
        private void ResetControls()
        {
            foreach (Button control in controls)  
            {
                control.BackColor = Color.Transparent;
                control.Text = GenerateRandomLetter().ToString();
            }
        }

        /// <summary>
        /// Updates any control not set
        /// </summary>
        private void UpdateControls()
        {
            foreach (Button control in controls)
                if (control.BackColor != Color.Green)
                {
                    control.BackColor = Color.Transparent;
                    control.Text = GenerateRandomLetter().ToString();
                }
        }

        /// <summary>
        /// Generates a random letter from the English alphabet
        /// </summary>
        /// <returns>random letter</returns>
        private char GenerateRandomLetter()
        {
            return alphabet[rnd.Next(alphabet.Length)];
        }
        
        /// <summary>
        /// Filter words list by user selection
        /// </summary>
        /// <param name="index">Selected control</param>
        /// <param name="letter">Current text of control</param>
        private void FilterWords(int index, char letter)
        {
            // search for word that contain the selected letter at selected index
            var newWords = (from word in words
                            where word[index] == letter
                            select word).ToList();

            if (newWords.Count > 0)
            {
                // set control selected by user
                controls[index].BackColor = Color.Green;

                // Look for distinct combinations of letters given by selected letter
                ForcingAlgorithm(ref newWords);

                // Update words list
                words.Clear();
                words.AddRange(newWords);

                // Update list box
                InitializeListbBox();
            }
            else
                controls[index].BackColor = Color.Red;
        }

        /// <summary>
        /// Checks for repeated characters by index in the list param
        /// </summary>
        /// <param name="newWords">Reference to list</param>
        private void ForcingAlgorithm(ref List<string> newWords)
        {
            // iterate over all 5 letters
            for (int i = 0; i < 5; i++)
            {
                // check only controls that have not been set
                if (controls[i].BackColor != Color.Green)
                {
                    // sort param list by letter at given position i
                    var sortedWords = (from word in newWords
                                       orderby word[i]
                                       select word).ToList();

                    // Assign first word and last word of sorted list
                    var firstWord = sortedWords[0];
                    var lastWord = sortedWords[sortedWords.Count - 1];

                    // Check if letter of first word matches letter of last word at position i
                    if (firstWord[i] == lastWord[i])
                    {
                        controls[i].BackColor = Color.Green;
                        controls[i].Text = firstWord[i].ToString();
                    }
                }
            }
        }
        #endregion

        #region UI Event Handlers
        /// <summary>
        /// Start/stops timer
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void buttonTimer_Click(object sender, EventArgs e)
        {
            // Check text of button 
            if (buttonTimer.Text == "GO !")
            {
                timer.Start();
                buttonTimer.Text = "STOP !";
                labelStatus.Text = "Game Running";
            }
            else
            {
                timer.Stop();
                labelStatus.Text = "Game Stopped";
            }
        }

        /// <summary>
        /// Resets game
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void buttonReset_Click(object sender, EventArgs e)
        {
            // reset all components
            timer.Stop();
            InitializeWords();
            InitializeListbBox();
            ResetControls();
            buttonTimer.Text = "GO !";
            labelStatus.Text = "";
        }

        /// <summary>
        /// Handles button click
        /// </summary>
        /// <param name="sender">Control that was clicked</param>
        /// <param name="e"></param>
        private void control_Click(object sender, EventArgs e)
        {
            // validate user selection only if timer is enabled
            if (timer.Enabled)
            {
                switch (((Button)sender).Name)
                {
                    case "button1":
                        FilterWords(0, button1.Text[0]);
                        break;
                    case "button2":
                        FilterWords(1, button2.Text[0]);
                        break;
                    case "button3":
                        FilterWords(2, button3.Text[0]);
                        break;
                    case "button4":
                        FilterWords(3, button4.Text[0]);
                        break;
                    case "button5":
                        FilterWords(4, button5.Text[0]);
                        break;
                }
            }
        }

        /// <summary>
        /// Updates controls every 5 seconds
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void timer_Tick(object sender, EventArgs e)
        {
            UpdateControls();
        }
        #endregion

    }
}
