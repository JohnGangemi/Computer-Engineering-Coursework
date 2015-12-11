using System.Collections.Generic;

namespace Parser_WFA
{
    public class StandardCell
    {
        string cell_name = null;
        double cell_width = 0;
        double cell_length = 0;
        List<string> pins = new List<string>();

        public StandardCell(string name, double width, double length, List<string> io)
        {
            cell_name = name;
            cell_width = width;
            cell_length = length;
            pins = io;
        }

        public string get_cell_name()
        { return cell_name; }

        public double get_cell_width()
        { return cell_width; }

        public double get_cell_length()
        { return cell_length; }

        public double get_cell_area()
        { return cell_width * cell_length; }

        public List<string> get_cell_pins()
        { return pins; }
    }
}
