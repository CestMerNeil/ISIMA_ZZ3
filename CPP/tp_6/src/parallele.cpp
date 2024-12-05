#include <cstdlib>
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <future>

/*
int main() {
 return EXIT_SUCCESS;
}

*/

std::mutex mutx;
std::condition_variable condition;
unsigned compteur = 0;

void zzz(unsigned n)
{
    {
        std::scoped_lock<std::mutex> verrou(mutx);
        std::cout << "[" << n << "] zzz..." << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void esclave(unsigned n)
{
    std::unique_lock<std::mutex> verrou(mutx);
    std::cout << "[" << n << "] attend..." << std::endl;
    condition.wait(verrou, []()
                   { return compteur == 5; });
    std::cout << "[" << n << "] termine" << std::endl;
}

void maitre()
{
    for (unsigned i = 0; i < 5; ++i)
    {
        {
            std::scoped_lock<std::mutex> verrou(mutx);
            std::cout << "[0] compteur = " << compteur << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
        {
            std::scoped_lock<std::mutex> verrou(mutx);
            ++compteur;
        }
        condition.notify_all();
    }
}

void calcul(std::promise<double> p1, std::promise<double> p2)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    p1.set_value(3);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    p2.set_value(7);
}

int main()
{
    std::promise<double> p1, p2;
    std::future<double> f1 = p1.get_future();
    std::future<double> f2 = p2.get_future();
    std::future<void> f = std::async(std::launch::async, calcul,
                                     std::move(p1), std::move(p2));
    f1.wait();
    std::cout << "valeur1 = " << f1.get() << std::endl;
    f2.wait();
    std::cout << "valeur2 = " << f2.get() << std::endl;
}