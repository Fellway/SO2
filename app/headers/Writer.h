#ifndef SO2_WRITER_H
#define SO2_WRITER_H


class Writer {
private:
    int numberOfNumbers;
    int pauseTime;
    int replies;
public:
    explicit Writer(char *argv[]);
    void init(char *argv[]) const;
};


#endif
