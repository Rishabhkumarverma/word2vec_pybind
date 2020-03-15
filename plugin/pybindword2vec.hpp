
#ifndef _TRT_PROFILER_H_
#define _TRT_PROFILER_H_

#include <fstream>
#include <iostream>

#include"word2vec.hpp"


class CWord2Vec
{
public:
void readFile(const std::string &_fileName, std::string &_data);
int run(const std::string modelname, const std::string filename );
int myadd(int a , int b){return(a+b);}
    
};


void CWord2Vec::readFile(const std::string &_fileName, std::string &_data) {
    std::ifstream ifs;
    ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    ifs.open(_fileName.c_str());
    ifs.seekg(0, ifs.end);
    auto size = ifs.tellg();
    _data.resize(static_cast<std::size_t>(size), 0);
    ifs.seekg(0, ifs.beg);
    ifs.read(&_data[0], size);
    ifs.close();
}

int CWord2Vec::run(const std::string modelname, const std::string filename)
{

// load wor2vec model
    std::unique_ptr<w2v::w2vModel_t> w2vModel;
    try {
        w2vModel.reset(new w2v::w2vModel_t());
        // load w2v model file
        if (!w2vModel->load(filename)) {
            throw std::runtime_error(w2vModel->errMsg());
        }
    } catch (const std::exception &_e) {
        std::cerr << _e.what() << std::endl;
        return 2;
    } catch (...) {
        std::cerr << "unknown error" << std::endl;
        return 2;
    }

    // create doc2vec model
    w2v::d2vModel_t d2vModel(w2vModel->vectorSize());
    try {
        
        /* load independent_orly_shooting.txt text
         * We will try to find articles closest to this one.
        */
        std::string fileText ;
        readFile(std::string(modelname), fileText);
        //  text to vector
        w2v::doc2vec_t doc2vec(w2vModel, fileText);

        // get nearest article IDs from the model
        std::vector<std::pair<std::size_t, float>> nearest;
        d2vModel.nearest(doc2vec, nearest, d2vModel.modelSize());

        // output result set
        for (auto const &i:nearest) {
            std::cout << i.first << ": " << i.second << std::endl;
        }

        // finaly, save our doc2vec model
        if (!d2vModel.save("model.d2v")) {
            std::cerr << "Can not save model: " << d2vModel.errMsg() << std::endl;
        }
    } catch (const std::exception &_e) {
        std::cerr << _e.what() << std::endl;
        return 3;
    } catch (...) {
        std::cerr << "unknown error" << std::endl;
        return 3;
    }
 return 0;
}
#endif //_FULLY_CONNECTED_H
