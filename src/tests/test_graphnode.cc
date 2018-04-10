/*
 * Copyright 2009-2018 The VOTCA Development Team (http://www.votca.org)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#define BOOST_TEST_MAIN

#define BOOST_TEST_MODULE graphnode_test
#include <boost/test/unit_test.hpp>
#include <exception>
#include <cmath>
#include <votca/tools/graphnode.h>
#include <iostream>
using namespace std;
using namespace votca::tools;

// used for rounding doubles so we can compare them
double round_(double v, int p) {
  v *= pow(10, p);
  v = round(v);
  v /= pow(10, p);
  return v;
}

BOOST_AUTO_TEST_SUITE(graphnode_test)

BOOST_AUTO_TEST_CASE(constructors_test) { GraphNode gn; }

BOOST_AUTO_TEST_CASE(accessors_test) {
  GraphNode gn;

  BOOST_CHECK_EQUAL(gn == gn, true);
  BOOST_CHECK_EQUAL(gn.getStringId(), "");

  unordered_map<string, int> int_vals = {{"Num", 134}};
  unordered_map<string, double> double_vals = {{"Height", 159.32}};
  unordered_map<string, string> str_vals = {{"Name", "George"}};
  GraphNode gn2(int_vals, double_vals, str_vals);
  GraphNode gn3(int_vals, double_vals, str_vals);
  BOOST_CHECK_EQUAL(gn != gn2, true);
  BOOST_CHECK_EQUAL(gn2 == gn2, true);
  BOOST_CHECK_EQUAL(gn3 == gn2, true);
}

BOOST_AUTO_TEST_CASE(setters_test) {
  unordered_map<string, int> int_vals = {{"Num", 134}};
  unordered_map<string, double> double_vals = {{"Height", 159.32}};
  unordered_map<string, string> str_vals = {{"Name", "George"}};
  GraphNode gn2(int_vals, double_vals, str_vals);

  string str{"Num134Height159.32NameGeorge"};
  BOOST_CHECK_EQUAL(gn2.getStringId(), str);

  unordered_map<string, int> int_vals2 = {{"Second", 2}, {"First", 1}};
  gn2.setInt(int_vals2);
  str = "First1Second2Height159.32NameGeorge";
  BOOST_CHECK_EQUAL(gn2.getStringId(), str);

  unordered_map<string, double> double_vals2 = {{"Height", 159.32},
                                                {"Weight", 101.43}};
  gn2.setDouble(double_vals2);
  str = "First1Second2Height159.32Weight101.43NameGeorge";
  BOOST_CHECK_EQUAL(gn2.getStringId(), str);

  unordered_map<string, string> str_vals2 = {{"Name", "George"},
                                             {"Address", "Koogler St"}};
  gn2.setStr(str_vals2);
  str = "First1Second2Height159.32Weight101.43AddressKoogler StNameGeorge";
  BOOST_CHECK_EQUAL(gn2.getStringId(), str);
}

BOOST_AUTO_TEST_SUITE_END()