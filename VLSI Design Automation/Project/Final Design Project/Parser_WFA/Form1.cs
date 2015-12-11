
using System;
using System.Collections.Generic;
using System.IO;
using System.Windows.Forms;

namespace Parser_WFA
{
    public partial class main_window : Form
    {
        #region Variables
        // File IO variables
        string working_directory = null;
        string last_used_directory = "c:\\";
        string library_file_name = null;
        string padframe_file_name = null;
        string netlist_file_name = null;

        // Design data structures
        List<StandardCell> cells = new List<StandardCell>(); // stores list of all gates in the standard library
        List<Partition> finalPartitions = new List<Partition>(); // stores list of final partitions 
        List<string[]> design_structures = new List<string[]>(); // stores gate info from netlist
        List<string> design_inputs = new List<string>(); // stores list of overall inputs to circuit
        List<string> design_outputs = new List<string>(); // stores list of overall outputs from circuit
        string[] slices_substrings = null; //Total number of slices available
        Queue<int> gate_queue = new Queue<int>();
        string design_name = null; // netlist file name
        double slice_width = 0; 
        double slice_length = 0;
        #endregion

        public main_window()
        {
            InitializeComponent();
        }

        #region UI FUNCTIONS
        private void library_btn_Click(object sender, EventArgs e)
        {
            OpenFileDialog file_dialog = new OpenFileDialog();

            file_dialog.InitialDirectory = last_used_directory;
            file_dialog.Filter = "Library Files(*.lib)|*.lib";
            file_dialog.RestoreDirectory = true;

            if (file_dialog.ShowDialog() == DialogResult.OK)
            {
                // store library file path
                library_file_name = file_dialog.FileName;
                // store current working directory
                DirectoryInfo dir = Directory.GetParent(library_file_name);
                last_used_directory = dir.ToString();
                // display library file path
                library_txtbox.Text = library_file_name;
            }

        }

        private void padframe_btn_Click(object sender, EventArgs e)
        {
            OpenFileDialog file_dialog = new OpenFileDialog();

            file_dialog.InitialDirectory = last_used_directory;
            file_dialog.Filter = "Library Files(*.lib)|*.lib";
            file_dialog.RestoreDirectory = true;

            if (file_dialog.ShowDialog() == DialogResult.OK)
            {
                // store padframe file path
                padframe_file_name = file_dialog.FileName;
                // store current working directory
                DirectoryInfo dir = Directory.GetParent(padframe_file_name);
                last_used_directory = dir.ToString();
                // display padframe file path
                padframe_txtbox.Text = padframe_file_name;
            }
        }

        private void netlist_btn_Click(object sender, EventArgs e)
        {
            OpenFileDialog file_dialog = new OpenFileDialog();

            file_dialog.InitialDirectory = last_used_directory;
            file_dialog.Filter = "Netlist Files(*.netlblif, *netblif)|*.netlblif; *.netblif";
            file_dialog.RestoreDirectory = true;

            if (file_dialog.ShowDialog() == DialogResult.OK)
            {
                // store netlist file path
                netlist_file_name = file_dialog.FileName;
                // store current working directory
                DirectoryInfo dir = Directory.GetParent(netlist_file_name);
                last_used_directory = dir.ToString();
                // display netlist file path
                netlist_txtbox.Text = netlist_file_name;
            }
        }

        private void help_link_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            string message = "Click on 'Padframe' to select the desired padframe.\n" +
                            "Click on 'Cell Library' to select an approriate library to reference.\n" +
                            "Click on 'Netlist' to select the design to be partitioned.\n" +
                            "\nClick on 'Get Wrecked' to start partitioning algorithm.\n" +
                            "\nTeam:\n" +
                            "Steven Bell\n" +
                            "John Gangemi\n" +
                            "Chris Humphrey\n" +
                            "Austin Matthew\n" +
                            "Raj Patel";
            string caption = "How To...";

            MessageBox.Show(message, caption);
        }

        private void partition_btn_Click(object sender, EventArgs e)
        {
            // Reset all data structures
            reset_globals();

            // choose a folder to save output files above all else
            set_working_directory();
            while (working_directory == null)
            {
                set_working_directory();
            }

            parse_padframe();
            parse_netlist();
            parse_library();

            InitialPartition();

            // Print to file partition information
            List<string> partitionInfo = new List<string>();
            for (int i = 0; i < finalPartitions.Count; i++)
            {
                partitionInfo.Add("Partition " + (i + 1) + " " + finalPartitions[i].getWidth() + " x " + finalPartitions[i].getLength());

                partitionInfo.Add("Inputs: ");
                foreach (string[] io in finalPartitions[i].getPartitionInputs())
                {
                    foreach (string input in io)
                    {
                        partitionInfo.Add(input + " ");
                    }
                }

                partitionInfo.Add("Outputs: ");
                foreach (string output in finalPartitions[i].getPartitionOutputs())
                {
                    partitionInfo.Add(output + " ");
                }

                partitionInfo.Add(Environment.NewLine);
            }

            File.WriteAllLines(working_directory + @"\partition info.txt", partitionInfo.ToArray());
        }

        private void set_working_directory()
        {
            FolderBrowserDialog folder_dialog = new FolderBrowserDialog();
            folder_dialog.Description = "Choose a folder to store output files";

            // show folder dialog and wait for the user "response"
            if (folder_dialog.ShowDialog() == DialogResult.OK)
            {
                // store the selected folder path 
                working_directory = folder_dialog.SelectedPath;
            }
        }
        #endregion

        private void parse_netlist()
        {
            // parse netlist
            char[] separator = null; // null == whitespace

            // check if the file exists
            if (File.Exists(netlist_file_name))
            {
                // open the file
                using (FileStream fs = File.OpenRead(netlist_file_name))
                {
                    // iterate through the entire file by line
                    foreach (string line in File.ReadLines(netlist_file_name))
                    {
                        // parse the info
                        if (line.StartsWith(".model") )
                        {
                            string[] buffer = line.Split(separator, StringSplitOptions.RemoveEmptyEntries);
                            design_name = buffer[1];
                        }
                        else if (line.StartsWith(".inputs"))
                        {
                            string[] buffer = line.Split(separator, StringSplitOptions.RemoveEmptyEntries);

                            // add substrings of buffer array skipping the first substring (".inputs")
                            // and stopping before comments
                            for (int i = 1; i < buffer.Length - 1; i++)
                            {
                                if (buffer[i] == "#")
                                    break;

                                design_inputs.Add(buffer[i]);
                            }
                        }
                        else if (line.StartsWith(".outputs"))
                        {
                            string[] buffer = line.Split(separator, StringSplitOptions.RemoveEmptyEntries);

                            // add substrings of buffer array skipping the first substring (".outputs")
                            // and stopping before comments
                            for (int i = 1; i < buffer.Length - 1; i++)
                            {
                                if (buffer[i] == "#")
                                    break;

                                design_outputs.Add(buffer[i]);
                            }
                        }
                        else if (line.StartsWith(".gate"))
                        {
                            string[] buffer = line.Split(separator, StringSplitOptions.RemoveEmptyEntries);

                            for (int i = 2; i < buffer.Length; i++)
                            {
                                string io = buffer[i];
                                string temp = null;

                                for (int j = 2; j < io.Length; j++)
                                {
                                    temp += io[j];
                                }

                                buffer[i] = temp;
                            }

                            // add gate type to list
                            design_structures.Add(buffer);
                        }
                    }

                    // release all resources handling the file, i.e. close that bitch
                    fs.Close();
                }
            }
            else
            {
                string message = "Please choose a netlist";
                MessageBox.Show(message);
            }
        }

        private void parse_padframe()
        {
            // parse padframe to find area of grid slices
            // slice area = (usable horizontal area / # of horizontal slices) x (usable vertical area / # of vertical slices)

            char[] separator = null; // null == whitespace
            string[] usable_substrings = null;

            // check if the file exists
            if (File.Exists(padframe_file_name))
            {
                // open the file
                using (FileStream fs = File.OpenRead(padframe_file_name))
                {
                    // iterate through the entire file by line
                    foreach (string line in File.ReadLines(padframe_file_name))
                    {
                        // parse info by line
                        if (line.StartsWith(".USABLE"))
                        {
                            // store first 3 substrings separated by spaces
                            // index 0 = .USABLE, index 1 = <width>, index 2 = <length>
                            usable_substrings = line.Split(separator, StringSplitOptions.RemoveEmptyEntries);
                        }
                        else if (line.StartsWith(".SLICES"))
                        {
                            // store first 3 substrings separated by spaces
                            // index 0 = .SLICES, index 1 = <width>, index 2 = <length>
                            slices_substrings = line.Split(separator, StringSplitOptions.RemoveEmptyEntries);
                        }
                    }

                    // release all resources handling the file, i.e. close that bitch
                    fs.Close();
                }

                // calculate the slice area
                try
                {
                    slice_width = Convert.ToDouble(usable_substrings[1]) / Convert.ToDouble(slices_substrings[1]);
                    slice_length = Convert.ToDouble(usable_substrings[2]) / Convert.ToDouble(slices_substrings[2]);
                }
                catch
                {
                    string message = "Padframe is in wrong format and/or contains errors";
                    MessageBox.Show(message);
                }
            }
            else
            {
                string message = "Please choose a padframe";
                MessageBox.Show(message);
            }
        }

        private void parse_library()
        {
            // parse netlist
            char[] separator = null; // null == whitespace

            // check if the file exists
            if (File.Exists(library_file_name))
            {
                // open the file
                using (FileStream fs = File.OpenRead(library_file_name))
                {
                    // iterate all gates in the design
                    foreach (string[] gate in design_structures)
                    {
                        // iterate through the entire file by line
                        foreach (string line in File.ReadLines(library_file_name))
                        {
                            // parse the info
                            if (line.StartsWith(".cell"))
                            {
                                string[] buffer = line.Split(separator, StringSplitOptions.RemoveEmptyEntries);

                                if (buffer[1] == gate[1])
                                {
                                    List<string> io_pins = new List<string>();

                                    for (int i = 4; i < buffer.Length; i++)
                                    {
                                        io_pins.Add(buffer[i]);
                                    }

                                    cells.Add(new StandardCell(buffer[1], Convert.ToDouble(buffer[2]), Convert.ToDouble(buffer[3]), io_pins));

                                    break;
                                }
                            }
                        }
                    }

                    // release all resources handling the file, i.e. close that bitch
                    fs.Close();
                }
            }
            else
            {
                string message = "Please choose a cell library";
                MessageBox.Show(message);
            }
        }

        private void InitialPartition()
        {
            int partitionA_size = design_structures.Count / 2;
            int partitionB_size = design_structures.Count - partitionA_size;
            int[] partitionA = new int[partitionA_size];
            int[] partitionB = new int[partitionB_size];

            // populate the queue with gates from design structures based on index
            for (int i = 0; i < design_structures.Count; i++)
            {
                gate_queue.Enqueue(i);
            }

            int starting_element = gate_queue.Peek();
            int[] minimal_partitionA = new int[partitionA_size];
            int[] minimal_partitionB = new int[partitionB_size];
            int minimal_wire_cost = Int32.MaxValue;

            // perform algorithm to compute minimal wire cost and partition configs
            while (true)
            {
                List<int> external_wires = new List<int>();

                // partition current state of queue 
                int[] gate_array = gate_queue.ToArray();
                int partitionB_counter = 0;

                for (int i = 0; i < gate_queue.Count; i++)
                {
                    if (i < partitionA_size)
                    {
                        partitionA[i] = gate_array[i];
                        //Console.WriteLine("A = " + partitionA[i]);
                    }
                    else 
                    {
                        partitionB[partitionB_counter] = gate_array[i];
                        //Console.WriteLine("B = " + partitionB[partitionB_counter]);
                        partitionB_counter++;
                    }
                }

                // check outputs of partition A against inputs of partition B
                for (int i = 0; i < partitionA_size; i++)
                {
                    string[] partitionA_gate = design_structures[partitionA[i]];
                    string partitionA_output = partitionA_gate[partitionA_gate.Length - 1];

                    for (int j = 0; j < partitionB_size; j++)
                    {
                        string[] partitionB_gate = design_structures[partitionB[j]];

                        for (int k = 2; k < partitionB_gate.Length - 1; k++)
                        {
                            if (partitionA_output == partitionB_gate[k])
                            {
                                external_wires.Add((partitionA[i] * 10) + partitionB[j]);
                            }
                        }
                    }
                }

                // check outputs of partition B against inputs of partition A
                for (int i = 0; i < partitionB_size; i++)
                {
                    string[] partitionB_gate = design_structures[partitionB[i]];
                    string partitionB_output = partitionB_gate[partitionB_gate.Length - 1];

                    for (int j = 0; j < partitionA_size; j++)
                    {
                        string[] partitionA_gate = design_structures[partitionA[j]];

                        for (int k = 2; k < partitionA_gate.Length - 1; k++)
                        {
                            if (partitionB_output == partitionA_gate[k])
                            {
                                external_wires.Add((partitionA[j] * 10) + partitionB[i]);
                            }
                        }
                    }
                }

                // remove duplicate connections
                int num_external_wires = external_wires.Count;
                var dict = new Dictionary<int, int>();
                foreach (var value in external_wires)
                {
                    if (dict.ContainsKey(value))
                    {
                        num_external_wires--;
                    }
                }

                // calculate the minimal wire cost
                if (num_external_wires < minimal_wire_cost)
                {
                    minimal_wire_cost = num_external_wires;
                    partitionA.CopyTo(minimal_partitionA, 0);
                    partitionB.CopyTo(minimal_partitionB, 0);
                }

                // rotate queue
                int element = gate_queue.Dequeue();
                gate_queue.Enqueue(element);

                // check if queue has been fully rotated
                if (gate_queue.Peek() == starting_element)
                {
                    break;
                }

            } // end while

            // display optimal partitions
            Console.WriteLine("Optimal configuration for partition A: ");
            foreach (int gate_index in minimal_partitionA)
            {
                Console.WriteLine("Gate " + gate_index + " " + design_structures[gate_index].GetValue(1));
            }

            Console.WriteLine("Optimal configuration for partition B: ");
            foreach (int gate_index in minimal_partitionB)
            {
                Console.WriteLine("Gate " + gate_index + " " + design_structures[gate_index].GetValue(1));
            }

            Console.WriteLine("Minimal number of external wires: " + minimal_wire_cost);

            // calculate partition sizes
            double partitionA_width = 0;
            double partitionB_width = 0;
            double partitionA_length = 0;
            double partitionB_length = 0;

            foreach (int gate_index in minimal_partitionA)
            {
                partitionA_width += cells[gate_index].get_cell_width();
                partitionA_length += cells[gate_index].get_cell_length();
            }

            foreach (int gate_index in minimal_partitionB)
            {
                partitionB_width += cells[gate_index].get_cell_width();
                partitionB_length += cells[gate_index].get_cell_length();
            }

            Console.WriteLine("Partition A width = " + Convert.ToInt32(partitionA_width) + " and length = " + Convert.ToInt32(partitionA_length));
            Console.WriteLine("Partition B width = " + Convert.ToInt32(partitionB_width) + " and length = " + Convert.ToInt32(partitionB_length));

            Partition a = new Partition(Convert.ToInt32(partitionA_width), Convert.ToInt32(partitionA_length), minimal_partitionA, design_structures);
            Partition b = new Partition(Convert.ToInt32(partitionB_width), Convert.ToInt32(partitionB_length), minimal_partitionB, design_structures);
            finalPartitions.Add(a);
            finalPartitions.Add(b);

            // check partition sizes
            PartitionRecursive(a);
            PartitionRecursive(b);

            FloorPlan(finalPartitions);

        }

        private void nextPartition(Partition x)
        {
            Console.WriteLine(Environment.NewLine + "Size of partition x: " + x.getGates().Length);

            Queue<int> gate_queue = new Queue<int>();
            int partitionA_size = x.getGates().Length / 2;
            int partitionB_size = x.getGates().Length - partitionA_size;
            int[] partitionA = new int[partitionA_size];
            int[] partitionB = new int[partitionB_size];

            // populate the queue with gates from partition x based on index
            for (int i = 0; i < x.getGates().Length; i++)
            {
                gate_queue.Enqueue(i);
            }

            int starting_element = gate_queue.Peek();
            int[] minimal_partitionA = new int[partitionA_size];
            int[] minimal_partitionB = new int[partitionB_size];
            int minimal_wire_cost = Int32.MaxValue;

            // perform algorithm to compute minimal wire cost and partition configs
            while (true)
            {
                List<int> external_wires = new List<int>();

                // partition current state of queue 
                int[] gate_array = gate_queue.ToArray();
                int partitionB_counter = 0;

                for (int i = 0; i < gate_queue.Count; i++)
                {
                    if (i < partitionA_size)
                    {
                        partitionA[i] = gate_array[i];
                        //Console.WriteLine("A = " + partitionA[i]);
                    }
                    else
                    {
                        partitionB[partitionB_counter] = gate_array[i];
                        //Console.WriteLine("B = " + partitionB[partitionB_counter]);
                        partitionB_counter++;
                    }
                }

                // check outputs of partition A against inputs of partition B
                for (int i = 0; i < partitionA_size; i++)
                {
                    string[] partitionA_gate = design_structures[partitionA[i]];
                    string partitionA_output = partitionA_gate[partitionA_gate.Length - 1];

                    for (int j = 0; j < partitionB_size; j++)
                    {
                        string[] partitionB_gate = design_structures[partitionB[j]];

                        for (int k = 2; k < partitionB_gate.Length - 1; k++)
                        {
                            if (partitionA_output == partitionB_gate[k])
                            {
                                external_wires.Add((partitionA[i] * 10) + partitionB[j]);
                            }
                        }
                    }
                }

                // check outputs of partition B against inputs of partition A
                for (int i = 0; i < partitionB_size; i++)
                {
                    string[] partitionB_gate = design_structures[partitionB[i]];
                    string partitionB_output = partitionB_gate[partitionB_gate.Length - 1];

                    for (int j = 0; j < partitionA_size; j++)
                    {
                        string[] partitionA_gate = design_structures[partitionA[j]];

                        for (int k = 2; k < partitionA_gate.Length - 1; k++)
                        {
                            if (partitionB_output == partitionA_gate[k])
                            {
                                external_wires.Add((partitionA[j] * 10) + partitionB[i]);
                            }
                        }
                    }
                }

                // remove duplicate connections
                int num_external_wires = external_wires.Count;
                var dict = new Dictionary<int, int>();
                foreach (var value in external_wires)
                {
                    if (dict.ContainsKey(value))
                    {
                        num_external_wires--;
                    }
                }

                // calculate the minimal wire cost
                if (num_external_wires < minimal_wire_cost)
                {
                    minimal_wire_cost = num_external_wires;
                    partitionA.CopyTo(minimal_partitionA, 0);
                    partitionB.CopyTo(minimal_partitionB, 0);
                }

                // rotate queue
                int element = gate_queue.Dequeue();
                gate_queue.Enqueue(element);

                // check if queue has been fully rotated
                if (gate_queue.Peek() == starting_element)
                {
                    break;
                }

            } // end while

            // display optimal partitions
            Console.WriteLine("Optimal configuration for partition A: ");
            foreach (int gate_index in minimal_partitionA)
            {
                Console.WriteLine("Gate " + gate_index + " " + design_structures[gate_index].GetValue(1));
            }

            Console.WriteLine("Optimal configuration for partition B: ");
            foreach (int gate_index in minimal_partitionB)
            {
                Console.WriteLine("Gate " + gate_index + " " + design_structures[gate_index].GetValue(1));
            }

            Console.WriteLine("Minimal number of external wires: " + minimal_wire_cost);

            // calculate partition sizes
            double partitionA_width = 0;
            double partitionB_width = 0;
            double partitionA_length = 0;
            double partitionB_length = 0;

            foreach (int gate_index in minimal_partitionA)
            {
                partitionA_width += cells[gate_index].get_cell_width();
                partitionA_length += cells[gate_index].get_cell_length();
            }

            foreach (int gate_index in minimal_partitionB)
            {
                partitionB_width += cells[gate_index].get_cell_width();
                partitionB_length += cells[gate_index].get_cell_length();
            }

            Console.WriteLine("Partition A width = " + Convert.ToInt32(partitionA_width) + " and length = " + Convert.ToInt32(partitionA_length));
            Console.WriteLine("Partition B width = " + Convert.ToInt32(partitionB_width) + " and length = " + Convert.ToInt32(partitionB_length));

            Partition a = new Partition(Convert.ToInt32(partitionA_width), Convert.ToInt32(partitionA_length), minimal_partitionA, design_structures);
            Partition b = new Partition(Convert.ToInt32(partitionB_width), Convert.ToInt32(partitionB_length), minimal_partitionB, design_structures);
            finalPartitions.Add(a);
            finalPartitions.Add(b);

            // check partition sizes
            PartitionRecursive(a);
            PartitionRecursive(b);
        }

        private void PartitionRecursive(Partition x)
        {
            if (x.getLength() > slice_length || x.getWidth() > slice_width )
            {
                finalPartitions.Remove(x);
                nextPartition(x);
            }
            else
            {
                return;
            }
        }

        private void FloorPlan(List<Partition> partition_list)
        {
            //Start from the bottom left of the slice and work up
            //Pick the biggest partition, then go down the line from biggest to smallest
            //Rotate partitions as needed
            //int largest_area = 0;
            //int indx_of_largest_part = 0;

            // partition current state of queue 
            int[] gate_array = gate_queue.ToArray();

            List<Slice> slice_list = new List<Slice>();
            Console.WriteLine();
            for (int i = 0; i < Convert.ToInt32(slices_substrings[1]) && i < Convert.ToInt32(slices_substrings[2]); i++)
            {
                Slice temp_slice = new Slice(Convert.ToInt32(slice_width), Convert.ToInt32(slice_length));
                slice_list.Add(temp_slice);
            }
            int j = 0, k = 0;
            int total_slices_used = 1;
            Boolean overflow = false;
            
            Boolean status = true; //Did the partition successful place in Slice?
            foreach (Partition partition in finalPartitions) //Place partitions in slice(s)
            {
                status = slice_list[j].fillSlice(finalPartitions[k].getWidth(), finalPartitions[k].getLength(), Convert.ToInt32(slice_width), Convert.ToInt32(slice_length), k);
                if (!status) //Go to new slice, place partition that couldn't fit in new slice.
                {
                    total_slices_used++;
                    j++;
                    if (j == Convert.ToInt32(slices_substrings[1]) - 1 || j == Convert.ToInt32(slices_substrings[2]) - 1)
                    {

                        //CONTINUE HERE
                        overflow = true;
                        Console.WriteLine("Slices won't fit in the padframe, please choose a larger padframe.");
                        return;
                    }
                    slice_list[j].fillSlice(finalPartitions[k].getWidth(), finalPartitions[k].getLength(), Convert.ToInt32(slice_width), Convert.ToInt32(slice_length), k);
                    k++;
                }
                else //Attempt to put next partition in slice
                {
                    k++;
                }
            }

            Console.WriteLine("Total Slices used: " + total_slices_used);

            //NEEDS WORK
            j = 0;
            foreach (Slice index in slice_list)
            {
                //Temp
                if ( j < total_slices_used)
                {
                    //
                    slice_list[j].printSlice(Convert.ToInt32(slice_width), Convert.ToInt32(slice_length),working_directory, j+1);
                    j++;
                }
            }

            return;

        }

        private void printIO(Partition a, Partition b)
        {
          Console.WriteLine("Partiton A inputs:");
          foreach (string[] inputs in a.getPartitionInputs())
          {
              foreach (string input in inputs)
              {
                  Console.Write(input + " ");
              }
          }
          Console.WriteLine(Environment.NewLine);
          Console.Write("Partiton A outputs:");
          foreach (string output in a.getPartitionOutputs())
          {
              Console.Write(output + " ");
          }
          Console.WriteLine(Environment.NewLine);

          Console.WriteLine("Partition B inputs:");
          foreach (string[] inputs in b.getPartitionInputs())
          {
              foreach (string input in inputs)
              {
                  Console.Write(input + " ");
              }
          }
          Console.WriteLine(Environment.NewLine);
          Console.WriteLine("Partiton B outputs:");
          foreach (string output in b.getPartitionOutputs())
          {
              Console.Write(output + " ");
          }
        }

        private void reset_globals()
        {
            // Design data structures
            cells = new List<StandardCell>();
            design_structures = new List<string[]>();
            design_inputs = new List<string>();
            design_outputs = new List<string>();
            finalPartitions = new List<Partition>();
            slices_substrings = null;
            gate_queue = new Queue<int>();
        }
    } 
}