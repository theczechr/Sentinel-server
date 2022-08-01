#pragma once
#include "Database.hpp"
#include <boost/algorithm/string/join.hpp> // boost::algorithm::join
#include <trantor/utils/Logger.h>

/*
 * Accounts table (uuid, username, recovery_phrase, status, last_login)
 * Messages table (sender uuid, receiver uuid, content, unix time, ?)
 */

namespace storage {
class Table {
public:
  Table() {}

  /*
   * @brief Create new table with columns in database
   * @note UTF-8 text encoding assumed
   *
   * @param[in] db			Instantiate Database
   * @param[in] table_name	Name of the table you want to create
   * @param[in] columns		Vector which holds a column name and datatype
   * with constraint - constraint UNIQUE doesn't work
   * @see Datatypes https://www.sqlite.org/datatype3.html
   * @see Constraints
   * https://www.tutorialspoint.com/sqlite/sqlite_constraints.htm
   */
  Table(std::string table_name,
        std::vector<std::pair<std::string, std::string>> columns) {
    this->table_name = table_name;
    create(columns);
  }

  /*
   * @brief Returns table name
   *
   * @return Table name in std::string
   */
  std::string get_table_name() const;

  /*
   * @brief Add row to table
   */
  void add_row(std::vector<std::string> row);

  /*
   * @brief Check if column exists in database
   *
   * @return True if column exist
   */
  bool column_exist(std::string column_name);

  /*
   * @brief Check if value exists in column
   *
   * @return True if value exist
   */
  bool value_exist(std::string column_name, std::string value);

  /*
   * @brief Update value in a column with existing value
   */
  void update_value(std::string column_name, std::string old_value,
                    std::string new_value);

  /*
   * @brief Update a specific row value
   */
  void update_value_where(std::string value_column, std::string value,
                          std::string condition_column,
                          std::string condition_value);

  /*
   * @brief Update a specific row value
   */
  void update_value_where_d(std::string value_column, std::string value,
                            std::string condition_column1,
                            std::string condition_value1,
                            std::string condition_column2,
                            std::string condition_value2);

  /*
   * @brief Delete rows that matches condition
   */
  void delete_rows_where(std::string condition_column,
                         std::string condition_value);

  /*
   * @brief Delete row that matches two conditions (for deleting account)
   */
  void delete_row_where_d(std::string condition_column1,
                          std::string condition_value1,
                          std::string condition_column2,
                          std::string condition_value2);

  /*
   * @brief Get value from row where is only one condition
   *
   * @return std::vector with row in it
   */
  std::vector<std::string> get_row_where(std::string condition_column,
                                         std::string condition_value);

  /*
   * @brief Get value from row where are two conditions
   *
   * @return std::vector with row in it
   */
  std::vector<std::string> get_row_where_d(std::string condition_column1,
                                           std::string condition_value1,
                                           std::string condition_column2,
                                           std::string condition_value2);

private:
  Database db;
  std::string table_name;
  void create(std::vector<std::pair<std::string, std::string>> &columns);
};
} // namespace storage
