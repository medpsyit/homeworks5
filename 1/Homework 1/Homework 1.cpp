#include "sql_query_builder.h"

int main()
{

    SqlSelectQueryBuilder query_builder;
    query_builder.AddColumn("name").AddColumn("phone")
        .AddFrom("students")
        .AddWhere("id", "42").AddWhere("name", "John");

    query_builder.BuildQuery();

    const std::map<std::string, std::string> long_where{
        {"id", "20"}, {"name", "Ivan"}, {"age", "20"}, {"status", "student"}
    };
    const std::vector<std::string> long_columns{
        "name", "phone", "age", "status", "town"
    };

    query_builder.AddWhere_many(long_where)
        .AddColumns_many(long_columns);

    query_builder.BuildQuery();

    AdvancedSqlSelectQueryBuilder advanced_query_builder;
    advanced_query_builder.AddColumns_many({ "name", "phone" })
        .AddFrom("students");
    advanced_query_builder.AddWhere_inequality("id>42");

    advanced_query_builder.BuildQuery();

    return 0;
}
