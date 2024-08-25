#include <crow.h>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

mongocxx::instance instance{}; // This should exist for the lifetime of your application
mongocxx::client mongo_client{mongocxx::uri{"mongodb://localhost:27017"}};

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/add_watched_video/<string>")
        .methods("PATCH"_method)
        ([&mongo_client](const crow::request& req, std::string userId){
            auto x = crow::json::load(req.body);
            if (!x)
                return crow::response(400, "Invalid JSON");

            try {
                std::string videoId = x["videoId"].s();
                auto collection = mongo_client["Youtube"]["users"];

                // Here, you'd implement the logic to update the user document
                bsoncxx::builder::basic::document update_builder;
                update_builder.append(kvp("$push", make_document(kvp("watchedVideos", videoId))));

                auto result = collection.update_one(
                    make_document(kvp("_id", bsoncxx::oid(userId))),
                    update_builder.extract()
                );

                if (result) {
                    return crow::response(200, "Video added to watched list");
                } else {
                    return crow::response(404, "User not found");
                }
            } catch (const std::exception& e) {
                return crow::response(500, e.what());
            }
        });

    app.port(8081).multithreaded().run();
}
