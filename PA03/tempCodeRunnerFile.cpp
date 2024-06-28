stream cin;
    try {
        cin.open("./sample/10.inp");
        if (cin.fail()) throw fstream::failure("Could not open file");
    } catch (const fstream::failure &e) {
        cerr << e.what();
    }