using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;

namespace Project_2
{
    public partial class MainForm : Form
    {
        #region GLOBAL VARS
        List<aRandomNumberGenerator> objects = new List<aRandomNumberGenerator>();
        Dictionary<int, int> dataPoints = new Dictionary<int, int>();
        string area = string.Empty; // defines name of chart area 
        string series = string.Empty; // defines name of chart series
        int selectedObject = 0; // identifies the currently selected object from the list box
        #endregion

        public MainForm()
        {
            InitializeComponent();

            // set-up chart area for chart control
            area = "plot";
            histogram.ChartAreas.Clear();
            histogram.ChartAreas.Add(area);
            histogram.ChartAreas[area].AxisX.Title = "Random Number";
            histogram.ChartAreas[area].AxisY.Title = "Instances";
        }

        #region UI METHODS
        /// <summary>
        /// Handles click event for Coin, Die, and Gaussian buttons.
        /// Adds textual description to list box and object to list container.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void object_Click(object sender, EventArgs e)
        {
            // validate user input for seed value
            if (!ValidSeed())
            {
                MessageBox.Show("Please enter a positive numeric seed.", "Invalid Seed", MessageBoxButtons.OK);
                txtbx_seed.Text = "Seed";
                txtbx_seed.Focus();
            }
            else
            {
                int seed = Convert.ToInt32(txtbx_seed.Text);

                // populate list box and object list according to button click events
                switch(((Button)sender).Name)
                {
                    case "btn_coin":
                        lstbx_objects.Items.Add("Coin (" + seed + ")");

                        if (seed != 0)
                            objects.Add(new aCoin(seed));
                        else
                            objects.Add(new aCoin());

                        break;
                    case "btn_die":
                        lstbx_objects.Items.Add("Die (" + seed + ")");

                        if (seed != 0)
                            objects.Add(new aDie(seed));
                        else
                            objects.Add(new aDie());

                        break;
                    case "btn_gaussian":
                        lstbx_objects.Items.Add("Gaussian (" + seed + ")");

                        if (seed != 0)
                            objects.Add(new aGaussian(seed));
                        else
                            objects.Add(new aGaussian());

                        break;
                }
            }
        }

        /// <summary>
        /// Handles click event for Stop button.
        /// Stops the graph from updating by invoking the timer's stop method.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btn_stop_Click(object sender, EventArgs e)
        {
            generationTimer.Stop();
        }

        /// <summary>
        /// Handles click event for Reset button.
        /// Resets global variables and form components.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btn_reset_Click(object sender, EventArgs e)
        {
            // stop graph from updating if necessary
            generationTimer.Stop();

            // remove items from the list box
            lstbx_objects.Items.Clear();

            // remove data from the chart
            histogram.Series.Clear();

            // reset timer interval and track bar to minimums
            generationTimer.Interval = 500;
            trkbar_graphSpeed.Value = 0;
            
            // reset seed text box
            txtbx_seed.Text = "Seed";
            txtbx_seed.Focus();

            // reset all global variables
            objects.Clear();
            dataPoints.Clear();
            series = string.Empty;
            selectedObject = 0;
        }

        /// <summary>
        /// Handles SelectedIndexChanged event for List Box.
        /// Creates a graph and starts the timer.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void lstbx_objects_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (lstbx_objects.SelectedIndex >= 0)
            {
                selectedObject = lstbx_objects.SelectedIndex;

                BuildChart();
                BuildDictionary();
                generationTimer.Start();
            }
            else
                MessageBox.Show("Please select an object from the list.", "Invalid Selection", MessageBoxButtons.OK);
        }

        /// <summary>
        /// Handles Tick event for Timer.
        /// Generates a random number for selected object and updates graph.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void generationTimer_Tick(object sender, EventArgs e)
        {
            int randomNum = objects[selectedObject].Next();
            dataPoints[randomNum] += 1;
            
            histogram.Series[series].Points.AddXY(randomNum, dataPoints[randomNum]);
        }

        /// <summary>
        /// Handles Scroll event for Track Bar.
        /// Updates the frequency for which the graph displays data.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void trkbar_graphSpeed_Scroll(object sender, EventArgs e)
        {
            generationTimer.Interval = trkbar_graphSpeed.Value > 0 ? 100 : 500;
        }
        #endregion

        #region HELPER METHODS
        /// <summary>
        /// Validates user input from the text box.
        /// </summary>
        /// <returns>validation of user input</returns>
        private bool ValidSeed()
        {
            string seed = txtbx_seed.Text.Trim();

            if (string.IsNullOrEmpty(seed))
                txtbx_seed.Text = "0";
            else
                foreach (char ch in seed)
                    if (!char.IsDigit(ch))
                        return false;

            return true;
        }

        /// <summary>
        /// Builds a dictionary based on selected object's range.
        /// </summary>
        private void BuildDictionary()
        {
            int low = objects[selectedObject].Low;
            int high = objects[selectedObject].High;

            dataPoints.Clear();
            for (int i = low; i < high + 1; i++)
                dataPoints[i] = 0;
        }

        /// <summary>
        /// Builds a new chart for the selected object.
        /// </summary>
        private void BuildChart()
        {
            series = lstbx_objects.SelectedItem.ToString();
            histogram.Series.Clear();
            histogram.Series.Add(series);
            histogram.Series[series].ChartType = SeriesChartType.Column;
            histogram.Series[series].ChartArea = area;
        }
        #endregion
    }
}
