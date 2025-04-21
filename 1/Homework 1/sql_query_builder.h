#ifndef QUERY_BUILDER_H
#define QUERY_BUILDER_H

#include <iostream>
#include <vector>
#include <map>

class SqlSelectQuery {
public:
	std::vector<std::string> column_name{};
	std::string table_name{};
	std::map<std::string, std::string> condition_where{};
	std::string query{};
};

class SqlSelectQueryBuilder {
protected:
	SqlSelectQuery sql_query;
public:
	SqlSelectQueryBuilder() {}

	SqlSelectQueryBuilder& AddFrom(const std::string& _from) noexcept;

	SqlSelectQueryBuilder& AddColumn(const std::string& _column) noexcept;

	SqlSelectQueryBuilder& AddWhere(const std::string& _where_col, const std::string& _where_value) noexcept;

	SqlSelectQueryBuilder& AddWhere_many(const std::map<std::string, std::string>& kv) noexcept;

	SqlSelectQueryBuilder& AddColumns_many(const std::vector<std::string>& columns) noexcept;

	virtual void BuildQuery();

};

class AdvancedSqlSelectQueryBuilder : public SqlSelectQueryBuilder {
	std::string where_inequality{};
public:
	AdvancedSqlSelectQueryBuilder& AddWhere_inequality(const std::string& _inequality) noexcept;
	void BuildQuery() override;
};

#endif /* QUERY_BUILDER_H */

