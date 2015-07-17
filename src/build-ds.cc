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
#include <vector>

void getDataSource(rapidjson::Writer<rapidjson::StringBuffer> &writer, T_DS &dados) {
    //rapidjson::Writer<rapidjson::StringBuffer> writer(s);
    std::stringstream sst;
    sst << "DS_1" << std::setfill('0') << std::setw(5) << dados.id;

//    writer.StartObject();
//    writer.String("dataSources");
    dados.ds_name = dados.name + std::to_string(dados.id);
    dados.ds_xid = sst.str();
//    writer.StartArray();
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
//    writer.EndArray();
//    writer.EndObject();
}

void getDataPoint(rapidjson::Writer<rapidjson::StringBuffer> &writer, T_DS &dados, long num_dp) {
    //rapidjson::Writer<rapidjson::StringBuffer> writer(s);

    std::string dp_xid, dp_name;

//    writer.StartObject();
//    writer.String("dataPoints");
//    writer.StartArray();
    for (int k = 0; k < num_dp; k++) {
        //sst.flush();
        std::stringstream sst, sdp;
        sst << "DP_" << std::setfill('0') << std::setw(3) << dados.id;
        sst << std::setfill('0') << std::setw(3) << std::to_string(k + 1);
        sst >> dp_xid;
        dp_name = "Point " + std::to_string(k + 1);
        //
        writer.StartObject();
        writer.String("xid"); //
        writer.String(dp_xid.c_str());
        writer.String("loggingType"); //
        writer.String("ON_CHANGE");
        writer.String("intervalLoggingPeriodType"); //
        writer.String("MINUTES");
        writer.String("intervalLoggingType"); //
        writer.String("INSTANT");
        writer.String("purgeType"); //
        writer.String("YEARS");
        writer.String("pointLocator"); //
        {
            writer.StartObject();
            writer.String("dataType"); //
            writer.String("BINARY");
            writer.String("changeType"); //
            {
                writer.StartObject();
                writer.String("type"); //
                writer.String("RANDOM_BOOLEAN");
                writer.String("startValue"); //
                writer.String("true");
                writer.EndObject();
            }
            writer.String("settable"); //
            writer.Bool(false);
            writer.EndObject();
        }
        writer.String("eventDetectors"); //
        writer.StartArray();
        writer.EndArray();
        writer.String("engineeringUnits"); //
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
        writer.String("discardExtremeValues"); // "discardExtremeValues":false,
        writer.Bool(false);
        writer.String("discardHighLimit"); // "discardHighLimit":1.7976931348623157E308,
        writer.Double(std::numeric_limits<double>::max());
        writer.String("discardLowLimit"); // "discardLowLimit":-1.7976931348623157E308,
        writer.Double(std::numeric_limits<double>::lowest());
        writer.String("enabled"); // "enabled":true,
        writer.Bool(dados.enabled);
        writer.String("intervalLoggingPeriod"); // "intervalLoggingPeriod":15,
        writer.Uint(15);
        writer.String("name"); // "name":"Porta01",
        writer.String(dp_name.c_str());
        writer.String("purgePeriod"); // "purgePeriod":1,
        writer.Uint(1);
        writer.String("textRenderer"); // textRenderer
        {
            writer.StartObject();
            writer.String("type"); //"type":"PLAIN",
            writer.String("PLAIN");
            writer.String("suffix"); //"suffix":""
            writer.String("");
            writer.EndObject();
        }
        writer.String("tolerance"); //"tolerance":0.0
        writer.Double(0.0);
        writer.EndObject();
    }
//    writer.EndArray();
//    writer.EndObject();
}

void generateData(rapidjson::StringBuffer &s, long num_dp, long num_ds) {
    rapidjson::Writer<rapidjson::StringBuffer> writer(s);
    std::vector<T_DS> dados_ds;

    writer.StartObject();
    writer.String("dataSources");
    writer.StartArray();
    for (int i = 1; i <= num_ds; i++) {
        T_DS ds_gen;
        ds_gen.id = i;
        ds_gen.name = "Andar ";
        getDataSource(writer, ds_gen);
        dados_ds.push_back(ds_gen);
    }
    writer.EndArray();

    if (num_dp > 0) {
        writer.String("dataPoints");
        writer.StartArray();
        for (auto dados : dados_ds) {
            getDataPoint(writer, dados, num_dp);
        }
        writer.EndArray();
    }
    writer.EndObject();
}
