//#include "database.hpp"
//
////void database::create(std::string name)
////{
////    LOG_INFO << "SQlite3 version " << SQLite::VERSION << " (" << SQLite::getLibVersion() << ")";
////    LOG_INFO << "SQliteC++ version " << SQLITECPP_VERSION;
////    LOG_INFO << "Creating new database: " << name;
////
////    name = name + ".db3";
////
////    if (utils::file_exist(name))
////        LOG_ERROR << "Database file already exist!";
////    else
////        SQLite::Database db(name, SQLite::OPEN_CREATE);
////        LOG_INFO << "Database file created successfully";
////}
//
//int main()
//{
//    try
//    {
//        // Open a database file in create/write mode
//        SQLite::Database db("users.db3", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
//        LOG_INFO << "SQLite database file '" << db.getFilename().c_str() << "' opened successfully";
//
//        // Create a new table with an explicit "id" column aliasing the underlying rowid
//        db.exec("DROP TABLE IF EXISTS users");
//        db.exec("CREATE TABLE users (id INTEGER PRIMARY KEY, value TEXT)");
//
//        // first row
//        int nb = db.exec("INSERT INTO test VALUES (NULL, \"test\")");
//        LOG_INFO << "INSERT INTO test VALUES (NULL, \"test\")\", returned " << nb;
//
//        // second row
//        nb = db.exec("INSERT INTO test VALUES (NULL, \"second\")");
//        LOG_INFO << "INSERT INTO test VALUES (NULL, \"second\")\", returned " << nb;
//
//        // update the second row
//        nb = db.exec("UPDATE test SET value=\"second-updated\" WHERE id='2'");
//        LOG_INFO << "UPDATE test SET value=\"second-updated\" WHERE id='2', returned " << nb;
//
//        // Check the results : expect two row of result
//        SQLite::Statement   query(db, "SELECT * FROM test");
//        LOG_INFO << "SELECT * FROM test :";
//        while (query.executeStep())
//        {
//            LOG_INFO << "row (" << query.getColumn(0) << ", \"" << query.getColumn(1) << "\")";
//        }
//
//        db.exec("DROP TABLE test");
//    }
//    catch (std::exception& e)
//    {
//        LOG_INFO << "SQLite exception: " << e.what();
//        return EXIT_FAILURE; // unexpected error : exit the example program
//    }
//
//    LOG_INFO << "everything ok, quitting";
//
//    return EXIT_SUCCESS;
//}