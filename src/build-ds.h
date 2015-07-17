/*
 * build-ds.h
 *
 *  Created on: Jul 10, 2015
 *      Author: gian
 */

#ifndef BUILD_DS_H_
#define BUILD_DS_H_

#include <string>
#include "rapidjson/stringbuffer.h"

typedef struct{
    long id;
    std::string name, ds_xid, ds_name;
    bool enabled=false;
}T_DS;

void generateData(rapidjson::StringBuffer &s, long num_dp, long num_ds, bool enbl);
void getDataSource(rapidjson::StringBuffer &s,T_DS &dados);
void getDataPoint(rapidjson::StringBuffer &s,T_DS &dados, long num_dp);

#endif /* BUILD_DS_H_ */
