#include "preprocessor.hpp"
#include "global_config.hpp"
#include <cmath>
#include <limits>
#include <assert.h>
#include <set>
#include <boost/algorithm/string.hpp> 

namespace COML {
    Preprocessor::Preprocessor() : predicted_real_value() {}

    void Preprocessor::load_prob_map_gcn(std::unordered_map<std::string, int>& mapper, 
                        int branching_policy ){        
        
        std::ifstream predicted_file("tmp.prob");
        if (! predicted_file){
            std::cout << "fail to read the predicted file \n" << std::endl;
            exit(-1);
        }
        std::string varname1;
        std::string varname2;

        double prob;

        int idx = 0;
        std::vector<std::string> result;
        while (predicted_file >> varname1 >> prob){
             //edge-based symetric
            if (strcmp(gconf.prob_str.c_str(), "tsp") == 0 || strcmp(gconf.prob_str.c_str(), "vrp") == 0){   
                result.clear();
                boost::split(result, varname1, boost::is_any_of("_")); 
                varname2 = result[1] + "_" + result[0];
                mapper[varname1] = idx;
                mapper[varname2] = idx;
            }else{  //node-based
                mapper[varname1] = idx;
            }

            predicted_real_value.push_back(prob);
            gconf.orderednames.push_back(varname1);
            idx++;
        }

        predicted_file.close();
    }

}
