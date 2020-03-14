from build import PyProfiler
path_model="/home/risverm/workspace/project/Word2vec/data/GoogleNews-vectors-negative300.bin"
path_doc= "/home/risverm/workspace/project/word2vec-master/examples/doc2vec/texts/bbc_brazil_meat.txt"
obj=PyProfiler.CPyProfiler()
print(obj.myadd(1,2))
print(obj.doc2vector(path_doc,path_model))
