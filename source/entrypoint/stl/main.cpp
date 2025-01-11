#include "classes/mediatypes.hpp"
#include "common.hpp"
#include "config.hpp"
#include "modules/database/mysql.hpp"
#include "modules/database/psql.hpp"
#include "core/core.hpp"
#include "modules/hardware/system/storage.hpp"

#if defined(USE_MYSQL_MARIADB) && defined(USE_POSTGRESQL) && defined(USE_SQLITE) && defined(USE_MSSQL) && defined(USE_ORACLE)
using namespace Cell::Modules::BuiltIn::Database;
#endif

#include "modules/network/webserver/webserver.hpp"
#include "modules/cryptography/md5.hpp"
#include "modules/cryptography/sha.hpp"
#include "modules/cryptography/rsa.hpp"
#include "modules/cryptography/aes.hpp"
#include "modules/cryptography/blowfish.hpp"
#include "modules/cryptography/des.hpp"
#include "core/convertor/text/text.hpp"

// #include <catch2/catch_all.hpp>
// #include <zmq.hpp>

#include <core/logger.hpp>

CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::Modules::BuiltIn::Network;
CELL_USING_NAMESPACE Cell::Modules::BuiltIn::Network::WebServer;

Response indexHandler(const Request& request) {
    Response response;
    response.setStatusCode(200);
    response.setContentType("text/html");
    response.setContent("<html>\n"
                        "<head>\n"
                        "<link rel=\"stylesheet\" type=\"text/css\" href=\"/templates/assets/css/bootstrap.min.css\">\n"
                        "<style>\n"
                        "    body {\n"
                        "        padding: 20px;\n"
                        "    }\n"
                        "    .jumbotron {\n"
                        "        background-color: #f8f9fa;\n"
                        "        padding: 20px;\n"
                        "    }\n"
                        "</style>\n"
                        "</head>\n"
                        "<body>\n"
                        "<div class=\"jumbotron\">\n"
                        "    <h1 class=\"display-4\">Welcome to the Index Page [C++" + std::string(LANGUAGE_STANDARD_VER) + "]!</h1>\n"
                                                             "    <h2 class=\"lead\">From Cell engine!</h2>\n"
                                                             "    <hr class=\"my-4\">\n"
                                                             "    <p>This is an example HTML page using Bootstrap styles.</p>\n"
                                                             "<p style=\"color: red; font-style: italic;\">Additional message: HTTPS/SSL mode is disabled!</p>\n"
                                                             "</div>\n"
                                                             "<script src=\"/templates/assets/js/bootstrap.bundle.min.js\"></script>\n"
                                                             "</body>\n"
                                                             "</html>\n");
    return response;
}

// Route Handlers
Response homeHandler(const Request& request) {
    Response response;
    response.setStatusCode(200);
    response.setContentType("text/plain");
    response.setContent("Welcome to the Home Page!");
    return response;
}

Response userHandler(const Request& request) {
    Response response;
    response.setStatusCode(200);
    response.setContentType("text/plain");
    response.setContent("User Page");
    return response;
}

Response dynamicUserHandler(const Request& request) {
    std::string userId = request.path()->substr(6); // Extract the user ID from the path
    Response response;
    response.setStatusCode(200);
    response.setContentType("text/plain");
    response.setContent("User ID: " + userId);
    return response;
}

Response adminHandler(const Request& request) {
    Response response;
    response.setStatusCode(200);
    response.setContentType("text/plain");
    response.setContent("Admin Page");
    return response;
}

Response redirectHandler(const Request& request) {
    Response response;
    response.setStatusCode(301);
    response.setHeader("Location", "/home");
    return response;
}

Response jsonHandler(const Request& request) {
    //    Response response;
    //    response.setStatusCode(200);
    //    response.setContentType("text/html");
    //    return response;
    //    Response response;
    //    response.setStatusCode(200);
    //    //    response.setContentType("text/plain");

           //    boost::json::object root; // Create a JSON object

           //    root.emplace("name", "Kambiz"); // Add a string value
           //    root.emplace("age", 34); // Add an integer value
           //    root.emplace("exclusive_developer", true); // Add a boolean value
           //    root.emplace("organization", "Genyleap LLC"); // Add a boolean value
           //    root.emplace("Role", "Founder & CEO"); // Add a boolean value

           //    boost::json::object channels; // Create a nested JSON object
           //    channels.emplace("telegram", "https://t.me/KambizAsadzadeh");
           //    channels.emplace("youtube", "https://youtube.com/@KambizAsadzadeh");
           //    channels.emplace("instagram", "https://instagram.com/KambizAsadzadeh");
           //    channels.emplace("twitter", "https://twitter.com/KambizAsadzadeh");

           //    root.emplace("channels", std::move(channels)); // Add the nested object to the root object

           //    boost::json::object address; // Create a nested JSON object
           //    address.emplace("city", "Urmia");
           //    address.emplace("country", "Iran");

           //    root.emplace("address", std::move(address)); // Add the nested object to the root object

           //    boost::json::array hobbies; // Create a JSON array
           //    hobbies.emplace_back("Nature");
           //    hobbies.emplace_back("Sport");
           //    hobbies.emplace_back("Music");
           //    hobbies.emplace_back("Animal");

           //    root.emplace("hobbies", std::move(hobbies)); // Add the array to the root object

           //    std::string jsonString = boost::json::serialize(root);

           //    response.setContentType("application/javascript");
           //    response.setContent(jsonString);
           //    return response;
    return Response();
}

Response error404Handler(const Request& request) {
    Response response;
    response.setStatusCode(404);
    response.setContentType("text/html");
    response.setContent("<html><body><h1>404 Not Found</h1><p>The requested page was not found.</p></body></html>");
    return response;
}

Response exceptionErrorHandler(const Request& request, const std::exception& exception) {
    Response response;
    response.setStatusCode(500);
    response.setContentType("text/html");
    response.setContent("<html><body><h1>404 Not Found</h1><p>The requested page was not found.</p></body></html>");
    return response;
}

//! Core engine
#include <core/core.hpp>
#include <core/core-concepts.hpp>
#include <core/core-meta.hpp>
#include <core/console.hpp>
#include <classes/taskmanager.hpp>

//! Modules!
#include <modules/built-in/network>
#include <modules/built-in/hardware>

int main()
{
    // Create an instance of the DiskStorage class
    Cell::Modules::BuiltIn::Hardware::DiskStorage diskStorage;

           // Get a list of available disks
    DiskList disks = diskStorage.getDisks();

           // Iterate over the disks and print basic information
    for (const auto& disk : disks)
    {
        std::cout << "Disk Name: " << disk << std::endl;

               // Retrieve detailed information about the disk
        auto details = diskStorage.getDiskDetails(disk);

        if (details)
        {
            std::cout << "   File System: " << details->fileSystem.value_or("N/A") << std::endl;
            std::cout << "   Total Space: " << details->totalSpace << " bytes" << std::endl;
            std::cout << "   Free Space: " << details->freeSpace << " bytes" << std::endl;
            std::cout << "   Available Space: " << details->availableSpace << " bytes" << std::endl;
            std::cout << "   Writable: " << (details->isWritable ? "Yes" : "No") << std::endl;
            std::cout << "   Readable: " << (details->isReadable ? "Yes" : "No") << std::endl;
        }
        else
        {
            std::cerr << "Failed to retrieve disk details for " << disk << std::endl;
        }

        std::cout << "--------------------------" << std::endl;
    }

    return 0;
}

// int main() {

//     auto engineController = Cell::System::EngineController();

//     auto& engine = engineController.getEngine();

//     Cell::Modules::BuiltIn::Hardware::DiskStorage diskStorage;

//     const auto diskDevicesOptional = diskStorage.getDiskDevices();

//     std::optional<Cell::Modules::BuiltIn::Hardware::DiskStorage::Specification> dt;

//     if (diskDevicesOptional) {
//         try {
//             auto diskDevices = CreateScope<Types::VectorString>(*diskDevicesOptional);
//             std::println("Available Disk Devices:");
//             for (const auto& disk : *diskDevices) {
//                 std::println("Disk: {}", disk);
//                 *dt = *diskStorage.getDiskDetails(disk.c_str());
//                 std::println("Disk: {} Details:", dt->name.value());
//             }


//         } catch (const Exception& e) {
//             (DeveloperMode::IsEnable) ? Utility::Log("Exception: " + FROM_CELL_STRING(e.what()), Cell::Utility::LoggerType::Critical) : DO_NOTHING;
//         }
//     }



//     // const auto diskDevicesOptional = diskStorage.getDiskDevices();

//     // if (diskDevicesOptional) {

//     //     try {

//     //         const auto diskDevices = CreateScope<Types::VectorString>();

//     //         diskDevices->reserve(diskDevicesOptional->size());

//     //         *diskDevices = *diskDevicesOptional;

//     //         std::cout << "Available Disk Devices:" << std::endl;

//     //         for (const auto& disk : *diskDevices) {
//     //             std::cout << "Disk: " << disk << std::endl;
//     //         }

//     //         diskDevices->clear();

//     //     } catch (const std::exception& e) {
//     //         std::cerr << "Exception: " << e.what() << std::endl;
//     //     }
//     // }

//            // std::string n, w, p;
//            // Cell::Abstracts::Concepts::User::UserCredentials user(n, w, p);

//            //        // Access and print the stored information
//            // std::cout << "Email: " << user.getEmail() << std::endl;
//            // std::cout << "Crypto Address: " << user.getCryptoAddress() << std::endl;
//            // std::cout << "Password: " << user.getPassword() << std::endl;


//            // if(engine.start())
//            // {

//            //     WebServer webServer(Cell::EventLoopType::EPOLL);
//            //     webServer.start(80);
//            // }


//            //    std::string input = "Kambiz";
//            //    std::string md5Hash = md5.hash(input);

//            //    std::cout << "Input: " << input << std::endl;
//            //    std::cout << "MD5 Hash: " << md5Hash << std::endl;

//            //    bool isValid = md5.validateHash(md5Hash);
//            //    std::cout << "Is Valid Hash? " << (isValid ? "Yes" : "No") << std::endl;

//            //    bool isMatch = md5.matchHash(input, md5Hash);
//            //    std::cout << "Is Match? " << (isMatch ? "Yes" : "No") << std::endl;

//            //    ///!
//            //    //! \brief inputBase
//            //    //!

//            //    Convertors::Text::TextConverter convertor;
//            //    std::string inputBase = "Hello, Base64!";
//            //    std::optional<std::string> encoded = convertor.textToBase64(input);
//            //    std::optional<std::string> decoded = convertor.base64ToText(*encoded);

//            //    if (encoded.has_value()) {
//            //        std::cout << "Input: " << input << std::endl;
//            //        std::cout << "Encoded: " << *encoded << std::endl;
//            //    } else {
//            //        std::cout << "Encoding failed." << std::endl;
//            //    }

//            //    if (decoded.has_value()) {
//            //        std::cout << "Decoded: " << *decoded << std::endl;
//            //    } else {
//            //        std::cout << "Decoding failed." << std::endl;
//            //    }


//            // Modules::BuiltIn::Cryptography::Sha sha;
//            // std::string input = "Kambiz";

//            // std::string sha256Hash = sha.hash(input, Cell::Modules::BuiltIn::Cryptography::Sha::Algorithm::SHA256);
//            // std::string sha512Hash = sha.hash(input, Cell::Modules::BuiltIn::Cryptography::Sha::Algorithm::SHA512);

//            //        // Example usage of validateHash and matchHash
//            // std::string hashToValidate = sha256Hash;
//            // bool isValid = sha.validateHash(input, hashToValidate, Cell::Modules::BuiltIn::Cryptography::Sha::Algorithm::SHA256);
//            // bool isMatch = sha.matchHash(input, hashToValidate, Cell::Modules::BuiltIn::Cryptography::Sha::Algorithm::SHA256);

//            // std::cout << "hashToValidate:" << hashToValidate << std::endl;
//            // std::cout << "isValid:" << isValid << std::endl;
//            // std::cout << "isMatch:" << isMatch << std::endl;

//            // try {

//            //        std::string plaintext = "Hello, World!";
//            //        std::vector<unsigned char> key = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF}; // 64-bit encryption key

//            //        // Convert the plaintext string to a vector of unsigned chars
//            //        std::vector<unsigned char> data(plaintext.begin(), plaintext.end());

//            //        // Encrypt the data
//            //        std::vector<unsigned char> encryptedData = BlowFish::encrypt(key, data);

//            //        // Decrypt the encrypted data
//            //        std::vector<unsigned char> decryptedData = BlowFish::decrypt(key, encryptedData);

//            //        // Convert the decrypted data back to a string
//            //        std::string decryptedText(decryptedData.begin(), decryptedData.end());

//            //        // Print the results
//            //        std::cout << "Plaintext: " << plaintext << std::endl;
//            //        std::cout << "Encrypted data: ";
//            //        for (const auto& byte : encryptedData) {
//            //            std::cout << std::hex << static_cast<int>(byte) << " ";
//            //        }
//            //        std::cout << std::endl;
//            //        std::cout << "Decrypted text: " << decryptedText << std::endl;
//            // } catch (const std::exception& e) {
//            //     std::cerr << "Error: " << e.what() << std::endl;
//            //     return 1;
//            // }

//            //    // Create an instance of RsaKeyGenerator with the desired key size
//            //    RsaKeyGenerator keyGenerator(RsaKeyGenerator::Size_4096);

//            //    // Generate the RSA key pair and save them to files
//            //    std::string privateKeyFile = "private_key.pem";
//            //    std::string publicKeyFile = "public_key.pem";
//            //    bool success = keyGenerator.generateKeys(privateKeyFile, publicKeyFile);

//            //    if (success) {
//            //        std::cout << "RSA key pair generated and saved successfully!" << std::endl;
//            //    } else {
//            //        std::cout << "Failed to generate RSA key pair." << std::endl;
//            //        return 1;
//            //    }

//            //    // Encrypt and decrypt example
//            //    std::string plaintext = "Hello, RSA!";
//            //    std::string ciphertext = keyGenerator.encrypt(plaintext);
//            //    std::string decryptedText = keyGenerator.decrypt(ciphertext);

//            //    std::cout << "Plaintext: " << plaintext << std::endl;
//            //    std::cout << "Ciphertext: " << ciphertext << std::endl;
//            //    std::cout << "Decrypted Text: " << decryptedText << std::endl;

//            //    // Export the public key to another file
//            //    std::string exportedPublicKeyFile = "exported_public_key.pem";
//            //    success = keyGenerator.exportPublicKey(exportedPublicKeyFile);

//            //    if (success) {
//            //        std::cout << "Public key exported to file: " << exportedPublicKeyFile << std::endl;
//            //    } else {
//            //        std::cout << "Failed to export public key." << std::endl;
//            //        return 1;
//            //    }

//            //    std::string privateKeyPath = "private_key.pem";
//            //    std::string csrPath = "csr.pem";
//            //    std::string commonName = "*.genyleap.com";
//            //    std::string organization = "Genyleap Organization";
//            //    std::string organizationalUnit = "IT Department";
//            //    std::string locality = "Urmia";
//            //    std::string state = "WestAzerbaijan";
//            //    std::string country = "IR";
//            //    std::string emailAddress = "dev@genyleap.com";

//            //    CSRGenerator generator;
//            //    if (generator.loadPrivateKey(privateKeyPath)) {
//            //        if (generator.generateCSR(csrPath, commonName, organization, organizationalUnit,
//            //                                  locality, state, country, emailAddress)) {
//            //            printf("CSR generated successfully.\n");
//            //        } else {
//            //            fprintf(stderr, "Error generating CSR.\n");
//            //        }
//            //    } else {
//            //        fprintf(stderr, "Error loading private key.\n");
//            //    }

//            //    CsrData csrData;

//            //    if (generator.decodeCSR(csrPath, csrData)) {
//            //        printf("CSR decoded successfully.\n");
//            //        printf("Common Name (CN): %s\n", csrData.commonName.value().c_str());
//            //        printf("Organization (O): %s\n", csrData.organization.value().c_str());
//            //        printf("Organizational Unit (OU): %s\n", csrData.organizationalUnit.value().c_str());
//            //        printf("Locality (L): %s\n", csrData.locality.value().c_str());
//            //        printf("State/Province (ST): %s\n", csrData.state.value().c_str());
//            //        printf("Country (C): %s\n", csrData.country.value().c_str());
//            //        printf("Email Address: %s\n", csrData.emailAddress.value().c_str());
//            //    } else {
//            //        fprintf(stderr, "Error decoding CSR.\n");
//            //    }


//            // return 0;

//            // Cleanup: Delete the generated key pair files (optional)
//     //    std::remove(privateKeyFile.c_str());
//     //    std::remove(publicKeyFile.c_str());


//            // Generate RSA key pair
//     //    RSA* rsaKeyPair = Rsa::generateKeyPair(2048);

//            //    std::cout << "rsaKeyPair:" << rsaKeyPair << std::endl;

//            //    // Encrypt and decrypt using RSA
//            //    std::string plaintext = "Hello, RSA!";
//            //    std::string ciphertext = Rsa::encrypt(plaintext, rsaKeyPair);
//            //    std::string decryptedText = Rsa::decrypt(ciphertext, rsaKeyPair);

//            //    std::cout << "Plaintext: " << plaintext << std::endl;
//            //    std::cout << "Ciphertext: " << ciphertext << std::endl;
//            //    std::cout << "Decrypted Text: " << decryptedText << std::endl;

//            //    // Sign and verify using RSA
//            //    std::string message = "Important message";
//            //    std::string signature = Rsa::sign(message, rsaKeyPair);
//            //    bool isValid = Rsa::verify(message, signature, rsaKeyPair);

//            //    std::cout << "Message: " << message << std::endl;
//            //    std::cout << "Signature: " << signature << std::endl;
//            //    std::cout << "Verification Result: " << (isValid ? "Valid" : "Invalid") << std::endl;

//            //    // Free the RSA key pair
//            //    RSA_free(rsaKeyPair);
//            //    std::string sourceFile = "/Users/compez/Documents/GitHub/cell/build/CoreInterface";
//            //    std::string compressedFile = "/Users/compez/Documents/GitHub/cell/build/CoreInterface.gz";
//            //    std::string decompressedFile = "/Users/compez/Documents/GitHub/cell/build/CoreInterface";

//            //    Cell::Globals::Compressor compressor;

//            //    // Compress a single file
//            //    try {
//            //        compressor.compressFile(sourceFile, false, Cell::Globals::CompressionLevel::Fastest, [](float progress) {
//            //            std::cout << "Compression progress: " << progress << "%" << std::endl;
//            //        });
//            //        std::cout << "File compressed successfully!" << std::endl;
//            //    } catch (const std::exception& ex) {
//            //        std::cout << "Compression failed: " << ex.what() << std::endl;
//            //    }

//            //    // Decompress a single file
//            //    try {
//            ////        compressor.decompressFile(compressedFile, true, [](float progress) {
//            ////            std::cout << "Decompression progress: " << progress << "%" << std::endl;
//            ////        });

//            //        std::cout << "File decompressed successfully!" << std::endl;
//            //    } catch (const std::exception& ex) {
//            //        std::cout << "Decompression failed: " << ex.what() << std::endl;
//            //    }

//            //    std::string cronExpression = "* * * * 3"; // Every day at 9:05
//            //    int executionDelay = 10; // Delay between executions (in seconds)
//            //    int executionDuration = 3600; // Duration of the program's execution (in seconds)
//            //    std::string timezone = "Asia/Tehran"; // Set the desired timezone for the cron job

//            //    Cell::CronJob cron(cronExpression, sendEmailNotification, executionDelay, executionDuration, timezone);
//            //    cron.start();


//            //    // Compress a directory
//            //    try {
//            //        compressor.compressDirectory("path/to/source/directory", true, true, 9, [](float progress) {
//            //            std::cout << "Compression progress: " << progress << "%" << std::endl;
//            //        });
//            //        std::cout << "Directory compressed successfully!" << std::endl;
//            //    } catch (const std::exception& ex) {
//            //        std::cout << "Compression failed: " << ex.what() << std::endl;
//            //    }

//            //    // Decompress a directory
//            //    try {
//            //        compressor.decompressDirectory("path/to/compressed/directory", true, true, [](float progress) {
//            //            std::cout << "Decompression progress: " << progress << "%" << std::endl;
//            //        });
//            //        std::cout << "Directory decompressed successfully!" << std::endl;
//            //    } catch (const std::exception& ex) {
//            //        std::cout << "Decompression failed: " << ex.what() << std::endl;
//            //    }




//            // if(engine.start())
//            // {
//            // try {
//            //     TaskManager taskManager(false, "tasks.txt");

//            //            // Add tasks
//            //            taskManager.addTask("1", "Task 1", "Description 1", 1, []() {
//            //                std::cout << "Running Task 1" << std::endl;
//            //            });

//            //            taskManager.addTask("2","Task 2", "Description 2", 2, []() {
//            //                std::cout << "Running Task 2" << std::endl;
//            //            });

//            //            taskManager.addTask("3","Task 3", "Description 3", 3, []() {
//            //                std::cout << "Running Task 3" << std::endl;
//            //            });

//            //            // Attempt to add a duplicate task
//            //            taskManager.addTask("3","Task 5", "Duplicate Task", 4, []() {
//            //                std::cout << "Running Duplicate Task" << std::endl;
//            //            });

//            //            // Sort tasks by priority
//            //            std::vector<Task> allTasks = taskManager.getTasks();
//            //            taskManager.sortTasksByPriority(allTasks);

//            //            // List tasks
//            //            taskManager.echoTasks();

//            //            taskManager.runTask("2");

//            //        } catch (const std::exception& ex) {
//            //            std::cout << "Exception occurred: " << ex.what() << std::endl;
//            //        }

//            //        std::cin.get();

//            // }

//            //    if(engine.start())
//            //    {
//            //        //        Router router;
//            //        //        Cell::Url url;
//            //        //        if(url.isBrowserAvailable())
//            //        //        {
//            //        //            url.openURL("https://localhost");
//            //        ////            url.openURL("https://localhost/user/128");
//            //        ////            url.openURL("https://localhost/js");
//            //        ////            url.openURL("https://localhost/notfound");
//            //        //        }
//            //        //        WebServer webServer(EventLoopType::SELECT);
//            //        //        router.addRoute("/", indexHandler);
//            //        //        router.addRoute("/admin", adminHandler);
//            //        //        router.addRoute("/user/{id}", dynamicUserHandler);
//            //        //        router.addRoute("/js", jsonHandler);

//            //        //        // Add static files.
//            //        //        webServer.setDocumentRoot("templates/assets/");

//            //        //        // Set the custom error page handler
//            //        //        webServer.setNotFoundHandler(error404Handler);

//            //        //        // Set the custom exceptions page handler
//            //        //        webServer.setExceptionHandler(exceptionErrorHandler);

//            //        //        webServer.enableSessions();
//            //        //        webServer.registerRouter(router);
//            //        //        webServer.setThreadPoolSize(4);
//            //        //        webServer.setSslCertFile("server.crt");
//            //        //        webServer.setSslKeyFile("server.key");
//            //        //        webServer.enableSSL(true);
//            //        //        webServer.setRateLimit(100);
//            //        //        webServer.start(443);

//            //        // Create an instance of the ApplicationRetriever class
//            //        Cell::Modules::BuiltIn::Utility::ApplicationRetriever appRetriever;

//            //        // Retrieve the names and versions of all installed applications
//            //        std::vector<std::pair<std::string, std::string>> installedApps = appRetriever.getInstalledApplications();

//            //        // Print the retrieved application names and versions
//            //        for (const auto& app : installedApps) {
//            //            std::cout << "Application: " << app.first << ", Version: " << app.second << std::endl;
//            //        }


//            //        Cell::Modules::BuiltIn::Utility::LibraryManager libraryManager;

//            //        std::vector<Cell::Modules::BuiltIn::Utility::Library> libraries = libraryManager.getInstalledLibraries();
//            //        for (const auto& library : libraries) {
//            //            std::cout << "Library: " << library.name << ", Version: " << library.version << std::endl;
//            //        }

//            //        std::string libraryName = "example";
//            //        bool isAvailable = libraryManager.isLibraryAvailable(libraryName);
//            //        std::cout << "Library '" << libraryName << "' is " << (isAvailable ? "available." : "not available.") << std::endl;



//            ////        // Filter the installed applications by category (e.g., "Graphics")
//            ////        std::string category = "Graphics";
//            ////        std::vector<std::pair<std::string, std::string>> filteredApps = appRetriever.filterByCategory(installedApps, category);

//            ////        // Print the filtered application names and versions
//            ////        std::cout << "Filtered Applications in the '" << category << "' category:" << std::endl;
//            ////        for (const auto& app : filteredApps) {
//            ////            std::cout << "Application: " << app.first << ", Version: " << app.second << std::endl;
//            ////        }

//            ////        // Sort the installed applications in descending order
//            ////        appRetriever.sortApplications(installedApps, false);

//            ////        // Print the sorted application names and versions
//            ////        std::cout << "Applications sorted in descending order:" << std::endl;
//            ////        for (const auto& app : installedApps) {
//            ////            std::cout << "Application: " << app.first << ", Version: " << app.second << std::endl;
//            ////        }



//            //    }

//            //    //!MYSQL
//            //    {
//            //        // Connection pool configuration
//            //        std::string host = "localhost";
//            //        unsigned int port = 3306;
//            //        std::string user = "root";
//            //        std::string password = "44064406";
//            //        std::string database = "tegradb";
//            //        unsigned int poolSize = 5;

//            //        // Create a connection pool
//            //        MySqlConnectionPool connectionPool(host, port, user, password, database, poolSize);

//            //        // Initialize the connection pool
//            //        connectionPool.initialize();

//            //        {
//            //            // Create a MySQLDatabaseConnection object with connection pooling
//            //            MySQLDatabaseConnection connection(connectionPool);
//            //            // Use the connection for database operations
//            //            if (connection.connect()) {
//            //                std::cout << "Connected to MySQL server!" << std::endl;

//            //                std::clog << "Conn Num: " << connection.getActiveConnectionsCount() << std::endl;

//            ////                // Execute a query
//            ////                std::string query = "INSERT INTO users (username, password) VALUES ('John Doe', 'john.doe@example.com')";
//            ////                bool success = connection.executeSync(query);
//            ////                if (success) {
//            ////                    std::cout << "Query executed successfully!" << std::endl;

//            ////                    // Get the last inserted ID
//            ////                    unsigned int lastInsertedID = connection.getLastInsertID();

//            ////                    // Print the last inserted ID
//            ////                    std::cout << "Last Inserted ID: " << lastInsertedID << std::endl;
//            ////                } else {
//            ////                    std::cout << "Failed to execute query: " << connection.getLastError() << std::endl;
//            ////                }
//            //                connection.disconnect();
//            //            } else {
//            //                std::cout << "Failed to connect to MySQL server: " << connection.getLastError() << std::endl;
//            //            }
//            //        } // The MySQLDatabaseConnection object will be destroyed here, releasing the connection back to the pool

//            //    }

//            // Assuming you have an instance of MySQLDatabaseConnection named 'connection'
//            // Create an instance of MySQLDatabaseConnection
//            //    MySQLDatabaseConnection connection("127.0.0.1", 3306, "root","44064406","tegradb");

//            // Connection pool configuration
//            //    std::string host = "localhost";
//            //    unsigned int port = 3306;
//            //    std::string user = "root";
//            //    std::string password = "44064406";
//            //    std::string database = "tegradb";
//            //    int poolSize = 5;


//            //    // Create a connection pool
//            //    MySqlConnectionPool connectionPool(host, port, user, password, database, poolSize);


//            //    // Initialize the connection pool
//            //    connectionPool.initialize();

//            //    // Get a connection from the pool
//            //    Cell::Types::SqlConnection connection = connectionPool.getConnection();

//            //    // Create a MySQLDatabaseConnection object
//            //    MySQLDatabaseConnection dbConnection(connectionPool);


//            //    // Insert values into the table
//            //    std::string insertSQL = "INSERT INTO users (username, password) VALUES (?, ?)";
//            //    std::vector<std::string> params;
//            //    params.push_back("1");
//            //    params.push_back("John Doe");

//            //    if (!dbConnection.executePreparedStatement(insertSQL, params)) {
//            //        std::string error = dbConnection.getLastError();
//            //        std::cout << "Insertion error: " << error << std::endl;
//            ////        dbConnection.disconnect();
//            //        return 1;
//            //    }



//            //    // Get the last inserted ID using the connection from the pool
//            //    unsigned int lastInsertedID = dbConnection.getLastInsertID(connection);

//            //    // Print the last inserted ID
//            //    std::cout << "Last Inserted ID: " << lastInsertedID << std::endl;

//            //    // Release the connection back to the pool
//            //    connectionPool.releaseConnection(connection);


//            //    try {

//            //        //     Connection pool configuration
//            //        std::string host = "localhost";
//            //        unsigned int port = 5432;
//            //        std::string user = "compez";
//            //        std::string password = "44064406";
//            //        std::string database = "compez";
//            //        int poolSize = 5;

//            //        // Create a connection pool
//            //        //    MySqlConnectionPool connectionPool(host, port, user, password, database, poolSize);
//            //        PostgreSqlConnectionPool connectionPool(host, port, user, password, database, poolSize);

//            //        // Initialize the connection pool
//            //        connectionPool.initialize();

//            //        // Get a connection from the pool
//            ////        Cell::Types::SqlConnection connection = connectionPool.getConnection();

//            //        // Create a MySQLDatabaseConnection object with connection pooling
//            //        PostgreSqlDatabaseConnection connection(connectionPool);


//            //        if (connection.connect()) {
//            //            std::cout << "Connected to Psql server!" << std::endl;

//            //            std::clog << "Conn Num: " << connection.getActiveConnectionsCount() << std::endl;

//            ////            // Execute a query
//            ////            std::string query = "INSERT INTO users (username, password) VALUES ('John Doe', 'john.doe@example.com')";
//            ////            bool success = connection.executeSync(query);
//            ////            if (success) {
//            ////                std::cout << "Query executed successfully!" << std::endl;

//            ////                // Get the last inserted ID
//            ////                unsigned int lastInsertedID = connection.getLastInsertID();

//            ////                // Print the last inserted ID
//            ////                std::cout << "Last Inserted ID: " << lastInsertedID << std::endl;
//            ////            } else {
//            ////                std::cout << "Failed to execute query: " << connection.getLastError() << std::endl;

//            ////            }
//            //            connection.disconnect();
//            //        } else {
//            //            std::cout << "Failed to connect to MySQL server: " << connection.getLastError() << std::endl;
//            //        }
//            ////        connectionPool.releaseConnection(connection);

//            //    } catch (const std::exception& e) {
//            //        std::clog << "What: " << e.what() << std::endl;
//            //    }




//            //        try {
//            ////            if (!dbConnection.connect()) {
//            //////                std::clog << dbConnection.getLastError() << std::endl;
//            ////                std::cout << "Disconnected!" << std::endl;
//            ////            } else {
//            ////                std::cout << "Connected!" << std::endl;
//            ////            }



//            //        } catch (const std::exception& e) {
//            //            std::clog << e.what() << std::endl;
//            //        }



//            //        // Perform batch processing by bundling multiple insert operations into a single transaction
//            //      //  dbConnection.beginTransaction();

//            ////        std::string insertSQL = "INSERT INTO users (username, password) VALUES (?, ?)";
//            ////        std::vector<std::string> params;
//            ////        params.push_back(dbConnection.escapeString("P"));
//            ////        params.push_back(dbConnection.escapeString("43"));
//            ////        if (!dbConnection.executePreparedStatementSync(insertSQL, params)) {
//            ////            std::cout << dbConnection.getLastError() << std::endl;
//            ////            dbConnection.rollbackTransaction();
//            ////            return 1;
//            ////        }


//            ////        std::cout << "Key:" << dbConnection.getTablePrimaryKey("users") << std::endl;

//            ////        for(auto i : dbConnection.getExistingIndexes("users"))
//            ////        {
//            ////            std::cout << "Index:" << i << std::endl;
//            ////        }


//            ////        std::cout << "indexExists:" << dbConnection.indexExists("users", "PRIMARY") << std::endl;

//            ////        unsigned int lastInsertedID = dbConnection.getLastInsertID();

//            ////        std::clog << "lastInsertID:" << lastInsertedID << std::endl;



//            //        //dbConnection.commitTransaction();

//            //        //        // Analyze the database schema and query patterns to optimize indexes
//            //        //        connection.optimizeIndexes();

//            //        //        // Get the list of existing indexes for a table
//            //        //        std::vector<std::string> existingIndexes = connection.getExistingIndexes("users");
//            //        //        for (const std::string& index : existingIndexes) {
//            //        //            std::cout << "Existing Index: " << index << std::endl;
//            //        //        }

//            //        //        // Create a new index
//            //        //        std::vector<std::string> columns = { "name" };
//            //        //        std::string newIndexName = "idx_users_name";
//            //        //        if (connection.createIndex("my_table", newIndexName, columns)) {
//            //        //            std::cout << "Index created successfully." << std::endl;
//            //        //        } else {
//            //        //            std::cout << "Failed to create index: " << connection.getLastError() << std::endl;
//            //        //        }

//            //        //        // Drop an existing index
//            //        //        std::string existingIndexName = "idx_users_value";
//            //        //        if (connection.dropIndex("users", existingIndexName)) {
//            //        //            std::cout << "Index dropped successfully." << std::endl;
//            //        //        } else {
//            //        //            std::cout << "Failed to drop index: " << connection.getLastError() << std::endl;
//            //        //        }

//            ////        // Insert values into the table
//            ////        std::string insertSQL = "INSERT INTO my_table (id, name) VALUES (?, ?)";
//            ////        std::vector<std::string> params;
//            ////        params.push_back("1");
//            ////        params.push_back("John Doe");

//            ////        if (!dbConnection.executePreparedStatement(insertSQL, params)) {
//            ////            std::string error = dbConnection.getLastError();
//            ////            std::cout << "Insertion error: " << error << std::endl;
//            ////            dbConnection.disconnect();
//            ////            return 1;
//            ////        }

//            //        // Disconnect from the MySQL server
//            //        dbConnection.disconnect();

//            //        return 0;
//            //    } else {
//            //        // Handle connection error
//            //        std::cout << dbConnection.getLastError() << std::endl;
//            //    }


//            //    // Create an instance of MySQLDatabaseConnection
//            //    MySQLDatabaseConnection connection("127.0.0.1", 3306, "root","44064406","tegradb");

//            //    // Create a MySQL database connection
//            ////    MySQLDatabaseConnection connection("localhost", "username", "password", "database");

//            //    // Connect to the MySQL server
//            //    if (!connection.connect()) {
//            //        std::string error = connection.getLastError();
//            //        std::cout << "Connection error: " << error << std::endl;
//            //        return 1;
//            //    }

//            //    // Create the table
//            //    std::string createTableSQL = "CREATE TABLE IF NOT EXISTS my_table (id INT PRIMARY KEY, name VARCHAR(50))";
//            //    if (!connection.executePreparedStatement(createTableSQL, {})) {
//            //        std::string error = connection.getLastError();
//            //        std::cout << "Table creation error: " << error << std::endl;
//            //        connection.disconnect();
//            //        return 1;
//            //    }

//            //    // Insert values into the table
//            //    std::string insertSQL = "INSERT INTO my_table (id, name) VALUES (?, ?)";
//            //    std::vector<std::string> params;
//            //    params.push_back("1");
//            //    params.push_back("John Doe");

//            //    if (!connection.executePreparedStatement(insertSQL, params)) {
//            //        std::string error = connection.getLastError();
//            //        std::cout << "Insertion error: " << error << std::endl;
//            //        connection.disconnect();
//            //        return 1;
//            //    }

//            //    // Disconnect from the MySQL server
//            //    connection.disconnect();




//            //    // Initialize the connection pool with a few connections
//            //    for (int i = 0; i < 5; ++i) {
//            //        std::shared_ptr<MySQLDatabaseConnection> connection = MySQLDatabaseConnection::getConnection("localhost", 3306, "user", "password", "database");
//            //        if (connection != nullptr) {
//            //            MySQLDatabaseConnection::releaseConnection(connection);
//            //        }
//            //    }

//            //    // Retrieve a connection from the pool
//            //    std::shared_ptr<MySQLDatabaseConnection> connection = MySQLDatabaseConnection::getConnection("localhost", 3306, "user", "password", "database");
//            //    if (connection != nullptr) {
//            //        // Use the connection for database operations

//            //        // Release the connection back to the pool when done
//            //        MySQLDatabaseConnection::releaseConnection(connection);
//            //    }


//            //    // Connect to the database
//            //    if (connection.connect()) {
//            //        std::cout << "Connected to the database." << std::endl;

//            //        // Create a table
//            //        std::string tableName = "empl";
//            //        std::vector<std::string> columns = {
//            //            "id INT PRIMARY KEY",
//            //            "name VARCHAR(100)",
//            //            "age INT",
//            //            "salary DECIMAL(10,2)"
//            //        };

//            //        if (connection.createTable(tableName, columns)) {
//            //            std::cout << "Table created successfully." << std::endl;

//            //            // Disable indexes and constraints (optional, if applicable)
//            //            connection.queryAsync("ALTER TABLE " + tableName + " DISABLE KEYS");

//            //            // Start the timer
//            //            auto startTime = std::chrono::steady_clock::now();

//            //            // Batch insert 10,000,000 rows into the table
//            //            std::vector<std::vector<std::string>> batchParams;
//            //            const int batchSize = 1000;

//            //            for (int i = 1; i <= 500'000; ++i) {
//            //                std::string name = "Employee " + std::to_string(i);
//            //                int age = 25 + i;
//            //                double salary = 5000.00 + i * 100;

//            //                std::vector<std::string> params = {
//            //                    std::to_string(i),
//            //                    name,
//            //                    std::to_string(age),
//            //                    std::to_string(salary)
//            //                };

//            //                batchParams.push_back(std::move(params));

//            //                // Execute batch insert every batchSize iterations
//            //                if (i % batchSize == 0) {
//            //                    if (!connection.executeBatchWithParams("INSERT INTO " + tableName + " (id, name, age, salary) VALUES (?, ?, ?, ?)", batchParams)) {
//            //                        std::cout << "Failed to insert batch starting at row " << (i - batchSize + 1) << std::endl;
//            //                    }

//            //                    batchParams.clear();
//            //                }
//            //            }

//            //            // Insert the remaining batch
//            //            if (!batchParams.empty()) {
//            //                if (!connection.executeBatchWithParams("INSERT INTO " + tableName + " (id, name, age, salary) VALUES (?, ?, ?, ?)", batchParams)) {
//            //                    std::cout << "Failed to insert the remaining batch." << std::endl;
//            //                }
//            //            }

//            //            // Enable indexes and constraints (optional, if applicable)
//            //            connection.execute("ALTER TABLE " + tableName + " ENABLE KEYS");

//            //            // Calculate the elapsed time
//            //            auto endTime = std::chrono::steady_clock::now();
//            //            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
//            //            std::cout << "Data insertion completed in " << duration << " milliseconds." << std::endl;
//            //        } else {
//            //            std::cout << "Failed to create table." << std::endl;
//            //        }

//            //        // Disconnect from the database (automatically called when the object goes out of scope)
//            //        connection.disconnect();
//            //    } else {
//            //        std::cout << "Failed to connect to the database." << std::endl;
//            //    }
//            //    return 0;
// }

//int main() {

//    std::unique_ptr<MySQLDatabaseConnection> dbConnection;

//    Cell::System::EngineController ec;
//    auto& engine = ec.getEngine();
//    if(engine.start())
//    {
//        std::cin.get();
//    }
//    // Connect to MySQL
////    dbConnection = std::make_unique<MySQLDatabaseConnection>("127.0.0.1", 3306, "root","44064406","tegradb");
//    // Create an instance of MySQLDatabaseConnection
////    MySQLDatabaseConnection connection("127.0.0.1", 3306, "root","44064406","tegradb");

//    // Connect to the database
////    if (connection.connect()) {

////        // Create a table
////        std::string tableName = "employees";
////        std::vector<std::string> columns = {
////            "id INT PRIMARY KEY",
////            "name VARCHAR(100)",
////            "age INT",
////            "salary DECIMAL(10,2)"
////        };

////        if (connection.createTable(tableName, columns)) {
////            std::cout << "Table created successfully." << std::endl;

////            // Disable indexes and constraints (optional, if applicable)
////            connection.execute("ALTER TABLE " + tableName + " DISABLE KEYS");

////            // Start the timer
////            auto startTime = std::chrono::steady_clock::now();

////            // Batch insert 10,000,000 rows into the table
////            std::vector<std::vector<std::string>> batchParams;
////            const int batchSize = 100;

////            for (int i = 1; i <= 500'000; ++i) {
////                std::string name = "Employee " + std::to_string(i);
////                int age = 25 + i;
////                double salary = 5000.00 + i * 100;

////                std::vector<std::string> params = {
////                    std::to_string(i),
////                    name,
////                    std::to_string(age),
////                    std::to_string(salary)
////                };

////                batchParams.push_back(std::move(params));

////                // Execute batch insert every batchSize iterations
////                if (i % batchSize == 0) {
////                    if (!connection.executeBatchWithParams("INSERT INTO " + tableName + " (id, name, age, salary) VALUES (?, ?, ?, ?)", batchParams)) {
////                        std::cout << "Failed to insert batch starting at row " << (i - batchSize + 1) << std::endl;
////                    }

////                    batchParams.clear();
////                }
////            }

////            // Insert the remaining batch
////            if (!batchParams.empty()) {
////                if (!connection.executeBatchWithParams("INSERT INTO " + tableName + " (id, name, age, salary) VALUES (?, ?, ?, ?)", batchParams)) {
////                    std::cout << "Failed to insert the remaining batch." << std::endl;
////                }
////            }

////            // Enable indexes and constraints (optional, if applicable)
////            connection.execute("ALTER TABLE " + tableName + " ENABLE KEYS");

////            // Calculate the elapsed time
////            auto endTime = std::chrono::steady_clock::now();
////            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
////            std::cout << "Data insertion completed in " << duration << " milliseconds." << std::endl;
////        } else {
////            std::cout << "Failed to create table." << std::endl;
////        }

////        // Disconnect from the database (automatically called when the object goes out of scope)
////        connection.disconnect();
////    } else {
////        std::cout << "Failed to connect to the database." << std::endl;
////    }


//    // The instance of MySQLDatabaseConnection will be destroyed automatically
//    // when it goes out of scope, calling the disconnect method in the destructor.

////    std::clog << connection.isConnected() << std::endl;


////    // Execute a query
////    std::string query = "SELECT * FROM teg_config_l";
////    std::vector<std::vector<std::string>> result = connection->query(query);

////    // Fetch the results
////    for (const auto& row : result) {
////        for (const auto& col : row) {
////            std::cout << col << " ";
////        }
////        std::cout << std::endl;
////    }


////    std::cout << "MySQL connection established!" << std::endl;

//    // Use the MySQL database connection for ORM operations

////    dbConnection->disconnect();


////    MySQLDatabaseConnection mySQLDb("127.0.0.1", 3306, "root","44064406","tegradb");
////    if(mySQLDb.connect())
////    {
////        std::cout << "Connected!/n";

//////        // create a new table called "employees" with two columns: "id" and "name"
//////        std::string sql = "CREATE TABLE employees (id INT PRIMARY KEY, name VARCHAR(255))";
//////        if (mySQLDb.execute(sql)) {
//////            std::cout << "Table created successfully" << std::endl;
//////        } else {
//////            std::cout << "Table creation failed" << std::endl;
//////        }


////        // Execute a query
////        std::string query = "SELECT * FROM teg_config_l";
////        std::vector<std::vector<std::string>> result = mySQLDb.query(query);

////        // Fetch the results
////        for (const auto& row : result) {
////            for (const auto& col : row) {
////                std::cout << col << " ";
////            }
////            std::cout << std::endl;
////        }


////    } else {
////        std::clog << "Not Connected!/n";
////    }

//    std::cin.get();

////    return 0;
//}
