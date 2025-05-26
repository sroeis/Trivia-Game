#include "Questions.h"
#include <curl/curl.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


std::unordered_map<std::string, int> Questions::categoryMap = {
{"Any", 0},
{"GeneralKnowledge", 9},
{"EntertainmentBooks", 10},
{"EntertainmentFilm", 11},
{"EntertainmentMusic", 12},
{"EntertainmentMusicalsAndTheatres", 13},
{"EntertainmentTelevision", 14},
{"EntertainmentVideoGames", 15},
{"EntertainmentBoardGames", 16},
{"ScienceAndNature", 17},
{"ScienceComputers", 18},
{"ScienceMathematics", 19},
{"Mythology", 20},
{"Sports", 21},
{"Geography", 22},
{"History", 23},
{"Politics", 24},
{"Art", 25},
{"Celebrities", 26},
{"Animals", 27},
{"Vehicles", 28},
{"EntertainmentComics", 29},
{"ScienceGadgets", 30},
{"EntertainmentJapaneseAnimeAndManga", 31},
{"EntertainmentCartoonAndAnimations", 32}
};

void Questions::getQuestions(int numOfQuestions, const std::string& category, const std::string& difficulty, SqliteDatabase & db)
{
	std::string URl = buildUrl(numOfQuestions, category, difficulty);
    std::cout << URl << std::endl;
	std::string response = getResponse(URl);

	nlohmann::json jsonResponse = nlohmann::json::parse(response);
     
    for (const auto& result : jsonResponse["results"]) 
    {
        std::string question = result["question"];
        std::string correct_answer = result["correct_answer"];
        std::vector<std::string> all_answers = result["incorrect_answers"];

        all_answers.push_back(correct_answer);
        //randomize
        std::random_device rd;
        std::default_random_engine rng(rd());
        std::shuffle(all_answers.begin(), all_answers.end(), rng); // Shuffle answers randomly

        // Find correct answer position
        int correctAnswerIndex = 1;
        for (int i = 0; i < all_answers.size(); ++i)
        {
            if (all_answers[i] == correct_answer)
            {
                correctAnswerIndex = i + 1;
                break;
            }
        }
        
        //std::cout << "Question:" << question << all_answers[0] << all_answers[1] << all_answers[2] << all_answers[3] << "Correct Answer: " << correct_answer << std::endl;
		db.insertQuestion(question, all_answers[0], all_answers[1], all_answers[2], all_answers[3], correctAnswerIndex);
    }
}

const std::string& Questions::buildUrl(int numOfQuestions, const std::string& category, const std::string& difficulty)
{
    std::string url = URL_1 + std::to_string(numOfQuestions);
    
    if (category != "Any") {
        int categoryNum = categoryMap[category];
        url += URL_2 + std::to_string(categoryNum);
    }
    
    url += URL_3 + difficulty + URL_4;
    return url;
}


const std::string& Questions::getResponse(const std::string& url)
{
    CURL* curl = curl_easy_init();
    if (!curl) {
        throw std::runtime_error("Failed to initialize CURL");
    }

    std::string response;
    
    // Set URL
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    
    // SSL Settings
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // Don't verify the peer's SSL certificate
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L); // Don't verify the certificate's name against host
    
    // Follow redirects
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    
    // Set timeout
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
    
    // Setup write callback
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, +[](void* contents, size_t size, size_t nmemb, void* userp) -> size_t {
        size_t realsize = size * nmemb;
        std::string* str = static_cast<std::string*>(userp);
        str->append(static_cast<char*>(contents), realsize);
        return realsize;
    });
    
    // Set write data
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // Perform request
    CURLcode res = curl_easy_perform(curl);
    
    // Cleanup
    curl_easy_cleanup(curl);
    
    if (res != CURLE_OK) {
        throw std::runtime_error(std::string("curl_easy_perform() failed: ") + curl_easy_strerror(res));
    }

    return response;
}