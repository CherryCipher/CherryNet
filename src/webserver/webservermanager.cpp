#include "WebServerManager.h"

/**
 * @brief Constructs a new WebServerManager.
 */
WebServerManager::WebServerManager()
{
}

/**
 * @brief Starts the HTTP server.
 *
 * @return true if the server started successfully.
 */
bool WebServerManager::start()
{
    if (running) return true;

    registerRoutes();
    server.begin();

    running = true;

    Serial.println("[WebServerManager] Web server started on port 80.");

    return true;
}

/**
 * @brief Stops the HTTP server.
 */
void WebServerManager::stop()
{
    if (!running) return;

    server.stop();
    running = false;

    Serial.println("[WebServerManager] Web server stopped.");
}

/**
 * @brief Returns whether the HTTP server is running.
 */
bool WebServerManager::isRunning() const
{
    return running;
}

/**
 * @brief Processes incoming HTTP requests.
 */
void WebServerManager::handleClients()
{
    if (!running) return;

    server.handleClient();
}

/**
 * @brief Registers all HTTP routes.
 */
void WebServerManager::registerRoutes()
{
    server.on("/", HTTP_GET, [this]()
    {
        serveIndex();
    });

    server.on("/api/status", HTTP_GET, [this]()
    {
        handleStatus();
    });

    server.onNotFound([this]()
    {
        handleNotFound();
    });
}

/**
 * @brief Serves the embedded main web interface.
 */
void WebServerManager::serveIndex()
{
    server.send(
        200,
        "text/html",
        Pages::INDEX
    );
}

/**
 * @brief Handles the system status API endpoint.
 */
void WebServerManager::handleStatus()
{
    server.send(
        200,
        "application/json",
        R"({
            "status":"online",
            "device":"ESP32"
        })"
    );
}

/**
 * @brief Sends a standard HTTP 404 response.
 */
void WebServerManager::handleNotFound()
{
    server.send(
        404,
        "text/html",
        Pages::ERROR404
    );

    Serial.println("[WebServerManager] 404 Not Found: " + server.uri());
}