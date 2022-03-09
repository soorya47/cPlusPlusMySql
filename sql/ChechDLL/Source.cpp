#include <jni.h>     
#include <fstream>
#include "Check.h"
#include "windows.h"
#include <mysql.h>
#include <cstdlib>
#include <iostream>
#include <jni.h> 
#include <cstdlib>
#include <iostream>
#include <filesystem>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

int main() {
    return 0;
}


void tokenize(std::string const& str, const char delim, std::vector<std::string>& out);
void tokenize(std::string const& str, const char delim, std::vector<std::string>& out)
{
	size_t start;
	size_t end = 0;

	while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
	{
		end = str.find(delim, start);
		out.push_back(str.substr(start, end - start));
	}
}


std::string toString(JNIEnv* env, jstring jStr);
std::string toString(JNIEnv* env, jstring jStr) {
    if (!jStr)
        return "";

    const jclass stringClass = env->GetObjectClass(jStr);
    const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    const jbyteArray stringJbytes = (jbyteArray)env->CallObjectMethod(jStr, getBytes, env->NewStringUTF("UTF-8"));

    size_t length = (size_t)env->GetArrayLength(stringJbytes);
    jbyte* pBytes = env->GetByteArrayElements(stringJbytes, NULL);

    std::string ret = std::string((char*)pBytes, length);
    env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

    env->DeleteLocalRef(stringJbytes);
    env->DeleteLocalRef(stringClass);
    return ret;
}

char host[] = "localhost";
char user[] = "root";
char pass[] = "user";

JNIEXPORT jboolean JNICALL Java_Check_addRow(JNIEnv* env, jobject thisObject, jstring row, jstring s1, jstring s2, jstring s3, jstring s4) {
	string name = toString(env, s1);
	string age = toString(env, s2);
	string dob = toString(env, s3);
	string city = toString(env, s4);
	string r = toString(env, row);

	string stmt;
	const char* sentence;

	MYSQL* obj;
	if (obj = mysql_init(0)) {
		
		if (mysql_real_connect(obj, host, user, pass, "sys", 3306, NULL, 0)) {
			cout << "connection established" << endl;
			stmt = "Insert INTO user(id,name,age,dob,city) VALUES (" + r + ",'" + name + "','" + age + "','" + dob + "','" + city + "')";
			sentence = stmt.c_str();
			if (mysql_query(obj, sentence)) {
				cout << "Error" << mysql_error(obj) << endl;
			}
			else {
				cout << "successfullly inserted" << endl;
			}
		}
		else {
			cout << "not valid" << endl;
		}


	}
	return true;
}


JNIEXPORT jboolean JNICALL Java_Check_removeRow
(JNIEnv* env, jobject thisObject, jstring s1) {
	string row = toString(env, s1);
	string stmt;
	const char* sentence;

	MYSQL* obj;
	if (obj = mysql_init(0)) {
	
		if (mysql_real_connect(obj, host, user, pass, "sys", 3306, NULL, 0)) {
			cout << "connection established" << endl;
			stmt = "DELETE FROM user WHERE id=" + row + "";
			sentence = stmt.c_str();
			if (mysql_query(obj, sentence)) {
				cout << "Error" << mysql_error(obj) << endl;
			}
			else {
				cout << "successfullly deleted" << endl;
			}
		}
		else {
			cout << "not valid" << endl;
		}

	}
	return true;
}


JNIEXPORT jboolean JNICALL Java_Check_updateRow
(JNIEnv* env, jobject thisObject, jstring r, jint c, jstring d) {
	string row = toString(env, r);
	int col = c;
	string data = toString(env, d);
	const char delim = ',';
	string line = "id,name,age,dob,city";
	std::vector<std::string> out;
	tokenize(line, delim, out);

	

	

	MYSQL* obj;
	if (obj = mysql_init(0)) {
		
		if (mysql_real_connect(obj, host, user, pass, "sys", 3306, NULL, 0)) {
			cout << "connection established" << endl;
			string stmt = "UPDATE user SET " + out[col] + " = '" + data + "' WHERE id = " + row + "";
			const char* sentence = stmt.c_str();
			if (mysql_query(obj, sentence)) {
				cout << "Error" << mysql_error(obj) << endl;
			}
			else {
				cout << "successfully updated" << endl;
			}
		}
		else {
			cout << "not valid" << endl;
		}

	}

	return true;

}

JNIEXPORT jint JNICALL Java_Check_searchRow
(JNIEnv* env, jobject thisObject, jint c, jstring d) {
	int col = c;
	string data = toString(env, d);
	const char delim = ',';
	string line = "id,name,age,dob,city";
	std::vector<std::string> out;
	tokenize(line, delim, out);MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "user", "sys", 3306, NULL, 0);

	if (conn) {
		cout << "connection established" << endl;

		string query = "SELECT * FROM user where "+out[col] + "='"+data+"'";
		const char* q = query.c_str();
		int qstate;
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				printf("ID: %s, Name: %s, age: %s,DOB: %s,city: %s\n", row[0], row[1], row[2],row[3],row[4]);
				char *str=row[0];
				cout << atoi(str) << endl;
				return atoi(str);
			}
		}
		else
		{
			cout << "Query failed: " << mysql_error(conn) << endl;
			return -1;
		}
	}
	else {
		puts("Connection to database has failed!");
	}

	cout << "Inside c++: error occured" << endl;
	return -1;
}
