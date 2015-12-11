Compile code with the following command:
g++ Vertex.cpp Edge.cpp Graph.cpp Main.cpp -o maze

Run the program with the following command:
./maze <input_file_path>

Output is saved in the current working directory to output.txt

Notes::
<input_file_path> requires a file location on disk.
If the input file path includes spaces, surround with quotes.

Examples::
If the input file path is not in the same directory as maze...
./maze c:\Users\JohnGangemi\Desktop\apollodiana.txt
./maze "c:\Users\JohnGangemi\Desktop\no squares.txt"

If the input file path is in the same directory as maze...
./maze apollodiana.txt
./maze "no squares.txt"

