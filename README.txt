
COMPILATION:

g++ -std=c++11 main.cpp

To change the graph file or the pattern file used by the program,

add the file path to globalDataStore.h ’s graph_file and pattern_file strings.

I have tested absolute paths and it works. however, you may try using relative paths.

NOTE:
Please make sure the files follow the following pattern

graph:
<nodeid>/tab<nodeid>
	OR
<nodeid,label>/tab<nodeid,label>

pattern:
<‘symbol’,predicateid>/tab<‘symbol’,predicateid>
			OR
<‘symbol’,predicateid,label>/tab<‘symbol’,predicateid,label>