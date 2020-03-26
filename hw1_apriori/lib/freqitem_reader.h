#ifndef _FREQITEM_READER_H
#define _FREQITEM_READER_H

#include <cstdio>
#include <cstdlib>

class FreqItemReader {

    public:
        FreqItemReader(const char* filename) {
            this->fp = fopen(filename, "r");
            this->filename = filename;
        }

        ~FreqItemReader() {
        }

        int* getFreqItem() {
            int header[3];

            if(fread(header, sizeof(int), 3, this->fp) == 3 && header[0] != header[1])
                return 0;

            int* buffer = (int*)malloc((sizeof(int) * header[2]) + 1);

            buffer[0] = header[2];
            if(header[2] != fread(buffer+1, sizeof(int), header[2], this->fp))
                return 0;

            return buffer;
        }

        void resetFilePointer() {
            fseek(this->fp, 0, SEEK_SET);
        }

    private:
        FILE* fp;
        fpos_t position;
        const char* filename;
};

#endif