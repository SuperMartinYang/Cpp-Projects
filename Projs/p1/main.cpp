// use TextQuery class
#include <TextQuery.h>

void print_result(const set<TextQuery::line_no>& locs, const string& sought, const TextQuery& tq){
    // if the word is find, then print count and all lines
    typedef set<TextQuery::line_no> line_nums;
    line_nums::size_type size = locs.size();
    cout << "\n" << sought << "occurs" << size << " " << make_plural(size, "time", "s") << endl;

    // print each occurance
    line_nums::const_iterator it = locs.begin();
    for (; it != locs.end(); it++){
        cout << "\t(line " << (*it + 1) << ") " << file.text_line(*it) << endl; 
    }
}

int main(int argc, char **argv){
    // open the file from which user will query words
    ifstream infile;
    if (argc < 2 || !open_file(infile, argv[1])){
        cerr << "No input file!" << endl;
        return EXIT_FAILURE;
    }
    TextQuery tq;
    tq.read_file(infile);
    // iterate with the use: prompt for a word to find and print results
    while (true){
        // prompt
        cout << "enter word to look for, or q to quit:";
        string s;
        cin >> s;
        // stop if hit eof on input or 'q' is entered
        if (!cin || s == "q") break;
        // get the set of line numbers on which this word happends
        set<TextQuery::line_no> locs = tq.run_query(s);
        // print count and all occurrences, if any
        print_results(locs, s, tq);
    }
    return 0;
}