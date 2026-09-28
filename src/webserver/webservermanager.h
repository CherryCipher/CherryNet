#pragma once

#include <Arduino.h>
#include <WebServer.h>

#include "Pages.h"

/**
 * @class WebServerManager
 * @brief Hosts an embedded web interface and REST API.
 *
 * The WebServerManager provides an HTTP server for ESP32 applications.
 *
 * Web content is compiled directly into the firmware and served from
 * program memory. No SD card or filesystem is required.
 *
 * Responsibilities
 * ----------------
 * - Start and stop the HTTP server.
 * - Register HTTP routes.
 * - Serve the embedded web interface.
 * - Handle REST API requests.
 * - Process incoming HTTP clients.
 *
 * Typical lifecycle
 * -----------------
 * @code
 * WebServerManager web;
 *
 * web.start();
 *
 * while (true)
 * {
 *     web.handleClients();
 * }
 * @endcode
 */
class WebServerManager
{
public:

    /**
     * @brief Constructs a new WebServerManager.
     */
    WebServerManager();

    /**
     * @brief Starts the HTTP server.
     *
     * Registers all routes and starts listening on port 80.
     *
     * @return true if the server started successfully.
     */
    bool start();

    /**
     * @brief Stops the HTTP server.
     */
    void stop();

    /**
     * @brief Processes incoming HTTP requests.
     *
     * Should be called continuously from the application's main loop.
     */
    void handleClients();

    /**
     * @brief Returns whether the web server is running.
     *
     * @return true if running.
     * @return false otherwise.
     */
    bool isRunning() const;

private:

    /**
     * @brief Registers all HTTP routes.
     */
    void registerRoutes();

    /**
     * @brief Handles the system status API endpoint.
     */
    void handleStatus();

    /**
     * @brief Serves the embedded main web interface.
     */
    void serveIndex();

    /**
     * @brief Sends a standard HTTP 404 response.
     */
    void handleNotFound();

private:

    /**
     * @brief Indicates whether the HTTP server is running.
     */
    bool running = false;

    /**
     * @brief Embedded HTTP server listening on port 80.
     */
    WebServer server{80};
};