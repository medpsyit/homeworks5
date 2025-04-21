#include "sql_query_builder.h"

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddFrom(const std::string& _from) noexcept {
	sql_query.table_name = _from;
	return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddColumn(const std::string& _column) noexcept {
	auto result{ std::find(sql_query.column_name.begin(), sql_query.column_name.end(), _column) };
	if (result == sql_query.column_name.end()) {
		sql_query.column_name.push_back(_column);
	}
	return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhere(const std::string& _where_col, const std::string& _where_value) noexcept {
	sql_query.condition_where[_where_col] = _where_value;
	return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhere_many(const std::map<std::string, std::string>& kv) noexcept {
	for (const auto& el : kv) {
		sql_query.condition_where[el.first] = el.second;
	}
	return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddColumns_many(const std::vector<std::string>& columns) noexcept {
	for (const auto& el : columns) {
		SqlSelectQueryBuilder::AddColumn(el);
	}
	return *this;
}

void SqlSelectQueryBuilder::BuildQuery() {

	if (sql_query.column_name.empty()) {
		sql_query.query = "SELECT * ";
	}
	else {
		sql_query.query = "SELECT ";
		size_t col_count = sql_query.column_name.size();
		if (col_count > 1) {
			for (size_t count = 0; count < col_count - 1; count++) {
				sql_query.query += sql_query.column_name[count] + ", ";
			}
		}
		sql_query.query += sql_query.column_name[col_count - 1] + " ";
	}

	if (sql_query.table_name.empty()) {
		std::cout << "Error! Enter the table name: ";
		std::string name{};
		std::cin >> name;
		sql_query.table_name = name;
	}
	sql_query.query += "FROM " + sql_query.table_name;

	if (!sql_query.condition_where.empty()) {
		sql_query.query += " WHERE ";
		size_t where_count = sql_query.condition_where.size();
		size_t count{ 1 };
		for (const auto& el : sql_query.condition_where)
			if (count == where_count) {
				sql_query.query += el.first + "=" + el.second;
			}
			else {
				sql_query.query += el.first + "=" + el.second + " AND ";
				count++;
			}
	}

	sql_query.query += ";";

	std::cout << "Your request is: " << sql_query.query << std::endl;

}

AdvancedSqlSelectQueryBuilder& AdvancedSqlSelectQueryBuilder::AddWhere_inequality(const std::string& _inequality) noexcept {
	where_inequality = _inequality;
	return *this;
}

void AdvancedSqlSelectQueryBuilder::BuildQuery(){
	if (sql_query.column_name.empty()) {
		sql_query.query = "SELECT * ";
	}
	else {
		sql_query.query = "SELECT ";
		size_t col_count = sql_query.column_name.size();
		if (col_count > 1) {
			for (size_t count = 0; count < col_count - 1; count++) {
				sql_query.query += sql_query.column_name[count] + ", ";
			}
		}
		sql_query.query += sql_query.column_name[col_count - 1] + " ";
	}

	if (sql_query.table_name.empty()) {
		std::cout << "Error! Enter the table name: ";
		std::string name{};
		std::cin >> name;
		sql_query.table_name = name;
	}
	sql_query.query += "FROM " + sql_query.table_name;

	if (!sql_query.condition_where.empty()) {
		sql_query.query += " WHERE ";
		size_t where_count = sql_query.condition_where.size();
		size_t count{ 1 };
		for (const auto& el : sql_query.condition_where)
			if (count == where_count) {
				sql_query.query += el.first + "=" + el.second;
			}
			else {
				sql_query.query += el.first + "=" + el.second + " AND ";
				count++;
			}
	}
	if (!where_inequality.empty()) {
		if (sql_query.condition_where.empty()) {
			sql_query.query += " WHERE ";
		}
		else {
			sql_query.query += " AND ";
		}
		sql_query.query += where_inequality;
	}

	sql_query.query += ";";

	std::cout << "Your advanced request is: " << sql_query.query << std::endl;

}
