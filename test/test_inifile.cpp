/*
 * test_inifile.cpp
 *
 * Created on: 26 Dec 2015
 *     Author: Fabian Meyer
 *    License: MIT
 */

//#include <catch.hpp>
#include "inicpp.h"
#include <assert.h>
#include <sstream>
#include <iostream>

void TEST_CASE()
{
    std::istringstream ss(("[Foo]\nbar=hello world\n[Test]"));
    ini::IniFile inif(ss);

    assert(inif.size() == 2);
    assert(inif["Foo"]["bar"].as<std::string>() == "hello world");
    assert(inif["Test"].size() == 0);
}

void TEST_CASE_a()
{
    std::istringstream ss("");
    ini::IniFile inif(ss);

    assert(inif.size() == 0);
}

void a_TEST_CASE()
{
    std::istringstream ss("# this is a comment");
    ini::IniFile inif(ss);

    assert(inif.size() == 0);
}


void ab_TEST_CASE()
{
    std::istringstream ss("[Foo]");
    ini::IniFile inif(ss);

    assert(inif.size() == 1);
    assert(inif["Foo"].size() == 0);
}

void abc_TEST_CASE()
{
    std::istringstream ss("[Foo]\nbar=");
    ini::IniFile inif(ss);

    assert(inif.size() == 1);
    assert(inif["Foo"].size() == 1);
    assert(inif["Foo"]["bar"].as<std::string>() == "");
}

void aaa_TEST_CASE()
{
    std::istringstream ss("[Foo]\nbar=hello\nbar=world");
    ini::IniFile inif(ss);

    assert(inif.size() == 1);
    assert(inif["Foo"].size() == 1);
    assert(inif["Foo"]["bar"].as<std::string>() == "world");
}

void test_TEST_CASE()
{
    std::istringstream ss("[Foo]\nbar1=1.2\nbar2=1\nbar3=-2.4");
    ini::IniFile inif(ss);

    assert(inif.size() == 1);
    assert(inif["Foo"].size() == 3);
    assert(inif["Foo"]["bar1"].as<double>() == 1.2);
    assert(inif["Foo"]["bar2"].as<double>() == 1.0);
    assert(inif["Foo"]["bar3"].as<double>() == -2.4);
}

void bb_TEST_CASE()
{
    std::istringstream ss("[Foo]\nbar1=1\nbar2=-2");
    ini::IniFile inif(ss);

    assert(inif.size() == 1);
    assert(inif["Foo"].size() == 2);
    assert(inif["Foo"]["bar1"].as<int>() == 1);
    assert(inif["Foo"]["bar2"].as<int>() == -2);
}

void lllTEST_CASE()
{
    std::istringstream ss("[Foo]\nbar1=true\nbar2=false\nbar3=tRuE");
    ini::IniFile inif(ss);

    assert(inif.size() == 1);
    assert(inif["Foo"].size() == 3);
    assert(inif["Foo"]["bar1"].as<bool>());
    //assert(inif["Foo"]["bar2"].as<bool>());
    assert(inif["Foo"]["bar3"].as<bool>());
}

void ao_TEST_CASE()
{
    std::istringstream ss("[Foo]\nbar1:true\nbar2:false\nbar3:tRuE");
    ini::IniFile inif(ss, ':');

    assert(inif.size() == 1);
    assert(inif["Foo"].size() == 3);
    assert(inif["Foo"]["bar1"].as<bool>());
    //REQUIRE_FALSE(inif["Foo"]["bar2"].as<bool>());
    assert(inif["Foo"]["bar3"].as<bool>());
}

void qw_TEST_CASE()
{
    std::istringstream ss("[Foo]\n# this is a test\nbar=bla");
    ini::IniFile inif(ss);

    assert(inif.size() == 1);
    assert(inif["Foo"].size() == 1);
    assert(inif["Foo"]["bar"].as<std::string>() == "bla");
}

void akkd_TEST_CASE()
{
    std::istringstream ss("[Foo]\n$ this is a test\nbar=bla");
    ini::IniFile inif(ss, '=', '$');

    assert(inif.size() == 1);
    assert(inif["Foo"].size() == 1);
    assert(inif["Foo"]["bar"].as<std::string>() == "bla");
}

void addkd_TEST_CASE()
{
    ini::IniFile inif;
    inif["Foo"]["bar1"] = true;
    inif["Foo"]["bar2"] = false;

    std::string result = inif.encode();
    assert(result == "[Foo]\nbar1=true\nbar2=false\n");
}

void ooo_TEST_CASE()
{
    ini::IniFile inif;
    inif["Foo"]["bar1"] = 1;
    inif["Foo"]["bar2"] = -2;

    std::string result = inif.encode();
    assert(result == "[Foo]\nbar1=1\nbar2=-2\n");
}

void qqq_TEST_CASE()
{
    ini::IniFile inif;
    inif["Foo"]["bar1"] = 1.2;
    inif["Foo"]["bar2"] = -2.4;

    std::string result = inif.encode();
    assert(result == "[Foo]\nbar1=1.2\nbar2=-2.4\n");
}

void iii_TEST_CASE()
{
    ini::IniFile inif(':', '#');
    inif["Foo"]["bar1"] = true;
    inif["Foo"]["bar2"] = false;

    std::string result = inif.encode();
    assert(result == "[Foo]\nbar1:true\nbar2:false\n");
}

int main(int argc, char *argv[]){
    (void)argc;
    (void)argv;

    try{

        ini::IniFile inif("/home/test/dbproxyserver.conf");
        std::cout<< inif["server"]["thread_num"].asString()<<std::endl;
        std::cout<< inif["master"]["host"].asString()<<std::endl;

    }catch (std::logic_error e){
        std::cout<<e.what()<<std::endl;
    }
    //iii_TEST_CASE();
}