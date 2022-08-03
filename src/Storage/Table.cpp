#include "Table.hpp"
#include <iostream>

void storage::Table::create(
    std::vector<std::pair<std::string, std::string>> &columns) {
  db.create_table(table_name);
  // Deleting temp. column
  for (const auto &column : columns) {
    std::cout << column.first << ", " << column.second;
    db.exec("ALTER TABLE " + table_name + " ADD COLUMN " + column.first + " " +
            column.second + "");
  }
  db.exec("ALTER TABLE " + table_name + " DROP COLUMN columnn");
}

std::string storage::Table::get_table_name() const { return table_name; }

void storage::Table::add_row(std::vector<std::string> row) {
  LOG_INFO << "Inserting items into table '" << table_name << "'";
  // Implode a vector of strings into a single string
  std::string row_s = boost::algorithm::join(row, "', '");

  db.exec("INSERT INTO " + table_name + " VALUES('" + row_s + "')");
}

bool storage::Table::column_exist(std::string column_name) {
  LOG_INFO << "Checking if '" << column_name << "' exist in database '"
           << db.get_name() << "'";

  // TODO

  return false;
}

bool storage::Table::value_exist(std::string column_name, std::string value) {
  LOG_INFO << "Checking if '" << column_name << "' exist in table '"
           << table_name << "'";

  if (db.get_db()
          .execAndGet("SELECT EXISTS(SELECT 1 FROM Accounts WHERE " +
                      column_name + " = '" + value + "')")
          .getString() == "0") {
    LOG_INFO << "Item '" << column_name << "' doens't exist";
    return false;
  }

  LOG_INFO << "Item '" << column_name << "' exist";
  return true;
}

void storage::Table::update_value(std::string column_name,
                                  std::string old_value,
                                  std::string new_value) {
  LOG_INFO << "Changing " << column_name << " from '" << old_value << "' to '"
           << new_value << "' in '" << table_name << "' table.";

  if (!value_exist(column_name, old_value)) {
    LOG_ERROR << "Value '" << old_value << "' doesn't exist, quitting";
    return;
  }

  db.exec("UPDATE " + table_name + " SET " + column_name + " = '" + new_value +
          "' WHERE " + column_name + " = '" + old_value + "'");
}

void storage::Table::update_value_where(std::string value_column,
                                        std::string value,
                                        std::string condition_column,
                                        std::string condition_value) {
  LOG_INFO << "Changing " << value_column << " to '" << value << "' where '"
           << condition_column << "' is '" << condition_value << "' in '"
           << table_name << "' table.";

  if (!value_exist(condition_column, condition_value)) {
    LOG_ERROR << "Condition value '" << condition_value
              << "' doesn't exist, quitting";
    return;
  }

  db.exec("UPDATE " + table_name + " SET " + value_column + " = '" + value +
          "' WHERE " + condition_column + " = '" + condition_value + "'");
}

void storage::Table::update_value_where_d(std::string value_column,
                                          std::string value,
                                          std::string condition_column1,
                                          std::string condition_value1,
                                          std::string condition_column2,
                                          std::string condition_value2) {
  LOG_INFO << "Changing " << value_column << " to '" << value << "' where c1 '"
           << condition_column1 << "' = '" << condition_value1 << "' and c2 '"
           << condition_column2 << "' = '" << condition_value2 << "' in '"
           << table_name << "' table.";

  if (!value_exist(condition_column1, condition_value1) ||
      !value_exist(condition_column2, condition_value2)) {
    LOG_ERROR << "One of the condition values doesn't exist, quitting";
    return;
  }

  db.exec("UPDATE " + table_name + " SET " + value_column + " = '" + value +
          "' WHERE " + condition_column1 + " = '" + condition_value1 +
          "' AND " + condition_column2 + " = '" + condition_value2 + "'");
}

void storage::Table::delete_rows_where(std::string condition_column,
                                       std::string condition_value) {
  LOG_INFO << "Deleting rows where '" << condition_column << "' = '"
           << condition_value << "' in '" << table_name << "' table.";

  if (!value_exist(condition_column, condition_value)) {
    LOG_ERROR << "Condition value '" << condition_value
              << "' doesn't exist, quitting";
    return;
  }

  db.exec("DELETE FROM " + table_name + " WHERE " + condition_column + " = '" +
          condition_value + "'");
}

void storage::Table::delete_row_where_d(std::string condition_column1,
                                        std::string condition_value1,
                                        std::string condition_column2,
                                        std::string condition_value2) {
  LOG_INFO << "Deleting row where c1 '" << condition_column1 << "' = '"
           << condition_value1 << "' and c2 '" << condition_column2 << "' = '"
           << condition_value2 << "' in '" << table_name << "' table.";

  if (!value_exist(condition_column1, condition_value1) ||
      !value_exist(condition_column2, condition_value2)) {
    LOG_ERROR << "One of the condition values doesn't exist, quitting";
    return;
  }

  db.exec("DELETE FROM " + table_name + " WHERE " + condition_column1 + " = '" +
          condition_value1 + "' AND " + condition_column2 + " = '" +
          condition_value2 + "'");
}

std::vector<std::string>
storage::Table::get_row_where(std::string condition_column,
                              std::string condition_value) {
  LOG_INFO << "Filling vector with row where '" << condition_column << "' = '"
           << condition_value << "' in '" << table_name << "' table.";

  // if (!value_exist(condition_column, condition_value))
  //{
  //	LOG_ERROR << "Condition value '" << condition_value << "' doesn't exist,
  // quitting";
  //	// Return something
  //
  // }

  std::vector<std::string> row;
  SQLite::Statement query(db.get_db(), "SELECT * FROM Accounts WHERE " +
                                           condition_column + " = '" +
                                           condition_value + "'");

  while (query.executeStep()) {
    for (int n{}; n < query.getColumnCount(); n++) {
      row.push_back(query.getColumn(n));
    }
  }
  return row;
}

std::vector<std::string> storage::Table::get_row_where_d(
    std::string condition_column1, std::string condition_value1,
    std::string condition_column2, std::string condition_value2) {
  LOG_INFO << "Filling vector with row where c1 '" << condition_column1
           << "' = '" << condition_value1 << "' and c2 '" << condition_column2
           << "' = '" << condition_value2 << "";

  if (!value_exist(condition_column1, condition_value1) ||
      !value_exist(condition_column2, condition_value2)) {
    throw "One of the condition values doesn't exist, quitting";
  }

  std::vector<std::string> row;
  SQLite::Statement query(
      db.get_db(), "SELECT * FROM Accounts WHERE " + condition_column1 +
                       " = '" + condition_value1 + "' AND " +
                       condition_column2 + " = '" + condition_value2 + "'");

  while (query.executeStep()) {
    for (int n{}; n < query.getColumnCount(); n++) {
      row.push_back(query.getColumn(n));
    }
  }
  return row;
}
