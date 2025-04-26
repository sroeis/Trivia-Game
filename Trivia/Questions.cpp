#include "Questions.h"

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

void Questions::getQuestions(int numOfQuestions, std::string category, std::string difficulty, SqliteDatabase db)
{
	std::string URl = buildUrl(numOfQuestions, category, difficulty);
	std::ostringstream response = getResponse(URl);

	nlohmann::json jsonResponse = nlohmann::json::parse(response.str());


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
		std::cout << "Question:" << question << all_answers[0] << all_answers[1] << all_answers[2] << all_answers[3] << "Correct Answer: " << correct_answer << std::endl;

		//db.insertQuestion(question, all_answers[0], all_answers[1], all_answers[2], all_answers[3], correctAnswerIndex);
    }
}

std::string Questions::buildUrl(int numOfQuestions, std::string category, std::string difficulty)
{


    if (category == "Any")
    {
        std::string url = URL_1 + std::to_string(numOfQuestions) + URL_3 + difficulty + URL_4;
    }
    int categoryNum = categoryMap[category];
	std::string url = URL_1 + std::to_string(numOfQuestions) + URL_2 + std::to_string(categoryNum) + URL_3 + difficulty + URL_4;
	return url;
    
}

std::ostringstream Questions::getResponse(std::string url)
{
    // Initialize the curl library
    curl_global_init(CURL_GLOBAL_DEFAULT);
    // Create a curl handle
    CURL* handle = curl_easy_init();
    // Set the URL to request
    curl_easy_setopt(handle, CURLOPT_URL, url);
    // Set the callback function to handle the response
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, [](char* data, size_t size, size_t nmemb, void* userp) {
        // Cast the user pointer to an ostream and write the data to it
        *static_cast<std::ostream*>(userp) << data;
        // Return the number of bytes processed
        return size * nmemb;
        });
    // Set the user pointer to be an ostream to which the response will be written
    std::ostringstream response;
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, &response);
    // Perform the request
    CURLcode result = curl_easy_perform(handle);
    // Check the result
    if (result != CURLE_OK) {
        // If the request failed, print an error message
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(result) << std::endl;
    }
    
    // Clean up
    curl_easy_cleanup(handle);
    curl_global_cleanup();
	return response;
}
