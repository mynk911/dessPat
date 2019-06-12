/**
 * \file cs180.cpp
 * \brief CS180 source file
 *
 * implementations for CS180
 *
 * \author Mayank Bansal
 */

#include "dbg.h"
#include "cs180.h"

#include <iostream>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <limits>
#include <vector>
#include <string>
#include <unordered_set>
#include <list>

namespace cs180 {
using sizeType = std::vector<std::string>::size_type;
//#define debugPrints
void populatePreferenceList(std::istream& in, sizeType* pref,
        std::vector < std::string >& preferer,
        std::vector < std::string >& preferee)
{
    std::string name;
    sizeType n = preferer.size();
    for(sizeType i = 0; i < n; i++)
    {
        in >> name;
        auto itr = std::lower_bound(preferer.begin(), preferer.end(), name);
        auto idx =static_cast<sizeType>(itr - preferer.begin());

        for(sizeType j = 0; j < n; j++)
        {
            in >> name;
            itr = std::lower_bound(preferee.begin(), preferee.end(), name);
            pref[idx * n + j] = static_cast<sizeType>(itr - preferee.begin());
        }
    }
}

void printPreferenceList(sizeType *pref,
        std::vector < std::string>& preferer,
        std::vector < std::string>& preferee)
{
    std::cout << "Preference list:" << std::endl;
    auto n = preferer.size();
    for(auto i = 0ul; i < n; i++)
    {
        std::cout << preferer.at(i) << " ";
        for(auto j = 0ul; j < n; j++)
        {
            std::cout << preferee.at(pref[i*n+j]) << " ";
        }
        std::cout << std::endl;
    }
}

bool checkForUniqueNames(std::vector< std::string> vec)
{
    std::unordered_set<std::string> s;
    for( auto& i : vec)
        s.insert(i);
    if(vec.size() != s.size() )
    {
        std::cout << "Names need to be unique";
        return false;
    }
    return true;
}

void calculateRankings(sizeType* r, const sizeType* p, sizeType n)
{
    for(sizeType i = 0; i < n; i++)
    {
        for(sizeType j = 0; j < n; j++)
        {
            r[n*i + p[n*i + j] ]= j;
        }
    }
}

int stable_matching(std::istream& in, std::ostream& out)
{
    sizeType n;
    std::cin >> n;
    std::vector< std::string > men, women;
    std::string name;
    for(sizeType i = 0; i < n; i++)
    {
        std::cin >> name;
        men.push_back(name);
    }
    if(!checkForUniqueNames(men)) return -1;
    for(sizeType i = 0; i < n; i++)
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
    auto* menPref = new sizeType[n*n];
    auto* womenPref = new sizeType[n*n];
    auto* ranking = new sizeType[n*n];
    auto* next = new sizeType[n];
    auto* current = new sizeType[n];

    populatePreferenceList(in, menPref, men, women);
    populatePreferenceList(in, womenPref, women, men);
#ifdef debugPrints
    printPreferenceList(menPref, men , women);
    printPreferenceList(womenPref, women, men);
#endif

    calculateRankings(ranking, womenPref, n);
    std::list<sizeType> freeProposers(n);
    std::iota(freeProposers.begin(), freeProposers.end(), 0);
    std::fill_n(next, n, 0);
    std::fill_n(current, n , std::numeric_limits<sizeType>::max());

    while (!freeProposers.empty())
    {
        auto m = freeProposers.front();
        assert(next[m] != n);
        auto w = menPref[m*n + next[m]];
        if(current[w] == std::numeric_limits<sizeType>::max())
        {
            current[w] = m;
            freeProposers.pop_front();
        }
        else{
            auto mo = current[w];
            if(ranking[w*n + m] < ranking[w*n + mo])
            {
                current[w] = m;
                freeProposers.pop_front();
                freeProposers.push_back(mo);
            }
        }
        next[m]++;
    }

    out << "stable matching:" << std::endl;
    for(sizeType i=0; i<n; i++)
    {
        out << women[i] << " " << men[current[i]] << std::endl;
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

}
