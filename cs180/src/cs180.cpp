/**
 * \file cs180.cpp
 * \brief CS180 source file
 *
 * implementations for CS180
 *
 * \author Mayank Bansal
 */

#include "cs180.h"

#include <iostream>
#include <algorithm>
#include <numeric>
#include <cassert>

#include <vector>
#include <string>
#include <unordered_set>
#include <list>

//#define debugPrints
void populatePreferenceList(int* pref,
        std::vector < std::string >& preferer,
        std::vector < std::string >& preferee)
{
    std::string name;
    int n = preferer.size();
    for(int i = 0; i < n; i++)
    {
        int idx;
        std::cin >> name;
        auto itr = std::lower_bound(preferer.begin(), preferer.end(), name);
        idx = itr - preferer.begin();

        for(int j = 0; j < n; j++)
        {
            std::cin >> name;
            itr = std::lower_bound(preferee.begin(), preferee.end(), name);
            pref[idx * n + j] = itr - preferee.begin();
        }
    }
}

void printPreferenceList(int *pref,
        std::vector < std::string>& preferer,
        std::vector < std::string>& preferee)
{
    std::cout << "Preference list:" << std::endl;
    int n = preferer.size();
    for(int i = 0; i < n; i++)
    {
        std::cout << preferer.at(i) << " ";
        for(int j = 0; j < n; j++)
        {
            std::cout << preferee.at(pref[i*n+j]) << " ";
        }
        std::cout << std::endl;
    }
}

bool checkForUniqueNames(std::vector< std::string> vec)
{
    std::unordered_set<std::string> s;
    for( auto i : vec)
        s.insert(i);
    if(vec.size() != s.size() )
    {
        std::cout << "Names need to be unique";
        return false;
    }
    return true;
}

void calculateRankings(int* r, const int* p, int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            r[n*i + p[n*i + j] ]= j;
        }
    }
}

int stable_matching()
{
    int n;
    std::cin >> n;
    std::vector< std::string > men, women;
    std::string name;
    for(int i = 0; i < n; i++)
    {
        std::cin >> name;
        men.push_back(name);
    }
    if(!checkForUniqueNames(men)) return -1;
    for(int i = 0; i < n; i++)
    {
        std::cin >> name;
        women.push_back(name);
    }
    if(!checkForUniqueNames(women)) return -1;

    std::sort(men.begin(), men.end());
    std::sort(women.begin(), women.end());
#ifdef debugPrints
    std::cout << "men:" << std::endl;
    for(auto i : men)
        std::cout << i << " ";
    std::cout << std::endl;
    std::cout << "women:" << std::endl;
    for(auto i : women)
        std::cout << i << " ";
    std::cout << std::endl;
#endif
#ifdef WIN32
    int* menPref = new int[n*n];
    int* womenPref = new int[n*n];
    int* ranking = new int[n*n];
    int* next = new int[n];
    int* current = new int[n];
#else
    int menPref[n*n], womenPref[n*n], ranking[n*n], next[n], current[n];
#endif
    populatePreferenceList(menPref, men, women);
    populatePreferenceList(womenPref, women, men);
#ifdef debugPrints
    printPreferenceList(menPref, men , women);
    printPreferenceList(womenPref, women, men);
#endif

    calculateRankings(ranking, womenPref, n);
    std::list<int> freeProposers(n);
    std::iota(freeProposers.begin(), freeProposers.end(), 0);
    std::fill_n(next, n, 0);
    std::fill_n(current, n , -1);

    while (!freeProposers.empty())
    {
        auto m = freeProposers.front();
        assert(next[m] != n);
        int w = menPref[m*n + next[m]];
        if(current[w] == -1)
        {
            current[w] = m;
            freeProposers.pop_front();
        }
        else{
            int mo = current[w];
            if(ranking[w*n + m] < ranking[w*n + mo])
            {
                current[w] = m;
                freeProposers.pop_front();
                freeProposers.push_back(mo);
            }
        }
        next[m]++;
    }

    std::cout << "stable matching:" << std::endl;
    for(int i=0; i<n; i++)
    {
        std::cout << women[i] << " " << men[current[i]] << std::endl;
    }
    if (menPref != nullptr)
        delete[] menPref;
    if (womenPref != nullptr)
        delete[] womenPref;
    if (ranking != nullptr)
        delete[] ranking;
    if (next != nullptr)
        delete[] next;
    if (current != nullptr)
        delete[] current;
    return 0;
}
