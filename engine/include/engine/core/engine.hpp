#pragma

class Engine {
    private:
        bool running = false;

    public:
        bool init();
        void run();
        void shutdown();
};