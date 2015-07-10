/*
 * build-ds.cc
 *
 *  Created on: Jul 10, 2015
 *      Author: gian
 */

#include "build-ds.h"
#include "rapidjson/writer.h"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <limits>

void getDataSource(rapidjson::StringBuffer &s, T_DS &dados) {
    rapidjson::Writer<rapidjson::StringBuffer> writer(s);
    std::stringstream sst;
    sst << "DS_1" << std::setfill('0') << std::setw(5) << dados.id;

    writer.StartObject();
    writer.String("dataSources");
//    writer.String("world");
//    writer.String("t");
//    writer.Bool(true);
//    writer.String("f");
//    writer.Bool(false);
//    writer.String("n");
//    writer.Null();
//    writer.String("i");
//    writer.Uint(123);
//    writer.String("pi");
//    writer.Double(3.1416);
//    writer.String("a");
//    for (unsigned i = 0; i < 4; i++)
//        writer.Uint(i);
    dados.ds_name = dados.name + std::to_string(dados.id);
    dados.ds_xid = sst.str();
    writer.StartArray();
    writer.StartObject();
    writer.String("xid");
    writer.String(sst.str().c_str());
    writer.String("type");
    writer.String("VIRTUAL");
    writer.String("updatePeriodType");
    writer.String("MINUTES");
    writer.String("enabled");
    writer.Bool(dados.enabled);
    writer.String("name");
    writer.String(dados.ds_name.c_str());
    writer.String("updatePeriods");
    writer.Uint(5);
    writer.EndObject();
    writer.EndArray();
    writer.EndObject();

    /*
     {
     "dataSources":[
     {
     "xid":"DS_312215",
     "type":"VIRTUAL",
     "updatePeriodType":"MINUTES",
     "enabled":true,
     "name":"Andar1_Estudo01",
     "updatePeriods":5
     }
     ]
     }
     */
}

void getDataPoint(rapidjson::StringBuffer &s, T_DS &dados, long num_dp) {
    rapidjson::Writer<rapidjson::StringBuffer> writer(s);

    std::string dp_xid;

    writer.StartObject();
    writer.String("dataPoints");
    writer.StartArray();
    for (int k = 0; k < num_dp; k++) {
        //sst.flush();
        std::stringstream sst;
        sst << "DP_" << std::setfill('0') << std::setw(3) << dados.id;
        sst << std::setfill('0') << std::setw(3) << std::to_string(k + 1);
        sst >> dp_xid;
        //
        writer.StartObject();
        writer.String("xid");//
        writer.String(dp_xid.c_str());
        writer.String("loggingType");//
        writer.String("ON_CHANGE");
        writer.String("intervalLoggingPeriodType");//
        writer.String("MINUTES");
        writer.String("intervalLoggingType");//
        writer.String("INSTANT");
        writer.String("purgeType");//
        writer.String("YEARS");
        writer.String("pointLocator");//
        {
            writer.StartObject();
            writer.String("dataType");//
            writer.String("BINARY");
            writer.String("changeType");//
            {   writer.StartObject();
                writer.String("type");//
                writer.String("RANDOM_BOOLEAN");
                writer.String("startValue");//
                writer.String("true");
                writer.EndObject();
            }
            writer.String("settable");//
            writer.Bool(false);
            writer.EndObject();
        }
        writer.String("eventDetectors");//
        writer.StartArray();
        writer.EndArray();
        writer.String("engineeringUnits");//
        writer.String("");
        writer.String("chartColour"); //"chartColour":null,
        writer.Null();
        writer.String("chartRenderer"); //"chartRenderer":null,
        writer.Null();
        writer.String("dataSourceXid"); //"dataSourceXid":"DS_312215",
        writer.String(dados.ds_xid.c_str());
        writer.String("defaultCacheSize"); //"defaultCacheSize":1,
        writer.Uint(1);
        writer.String("deviceName"); // "deviceName":"Andar1_Estudo01",
        writer.String(dados.ds_name.c_str());
        writer.String("discardExtremeValues");// "discardExtremeValues":false,
        writer.Bool(false);
        writer.String("discardHighLimit");// "discardHighLimit":1.7976931348623157E308,
        writer.Double(std::numeric_limits<double>::max());
        writer.String("discardLowLimit");// "discardLowLimit":-1.7976931348623157E308,
        writer.Double(std::numeric_limits<double>::lowest());
        writer.String("enabled");// "enabled":true,
        writer.Bool(dados.enabled);
        writer.String("intervalLoggingPeriod");// "intervalLoggingPeriod":15,
        writer.Uint(15);
        writer.String("name");// "name":"Porta01",
        writer.String(dp_name);
        writer.String("purgePeriod");// "purgePeriod":1,
        writer.Uint(1);
        writer.EndObject();
    }
    writer.EndArray();
    writer.EndObject();
    /*
     {
     "dataPoints":[
     {
     "xid":"DP_534715",
     "loggingType":"ON_CHANGE",
     "intervalLoggingPeriodType":"MINUTES",
     "intervalLoggingType":"INSTANT",
     "purgeType":"YEARS",
     "pointLocator":{
     "dataType":"BINARY",
     "changeType":{
     "type":"RANDOM_BOOLEAN",
     "startValue":"true"
     },
     "settable":false
     },
     "eventDetectors":[
     ],
     "engineeringUnits":"",
     "chartColour":null,
     "chartRenderer":null,
     "dataSourceXid":"DS_312215",
     "defaultCacheSize":1,
     "deviceName":"Andar1_Estudo01",
     "discardExtremeValues":false,
     "discardHighLimit":1.7976931348623157E308,
     "discardLowLimit":-1.7976931348623157E308,
     "enabled":true,
     "intervalLoggingPeriod":15,
     "name":"Porta01",
     "purgePeriod":1,
     "textRenderer":{
     "type":"PLAIN",
     "suffix":""
     },
     "tolerance":0.0
     }
     ]
     }
     */

}
