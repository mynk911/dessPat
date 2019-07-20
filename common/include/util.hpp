#include <iostream>
#include <set>

// Gets n tokens of input from stream in and inserts in seq. Checks 
// that all tokens are unique and returns sorted sequence if true.
template <typename SequenceContainer>
void SortUniqueRange(std::istream& in,
                     typename SequenceContainer::size_type n,
                     SequenceContainer& seq)
{
    seq.clear();
    typename SequenceContainer::value_type name;
    for(decltype(seq.size()) i = 0; i < n; i++)
    {
	in >> name;
	seq.push_back(name);
    }

    std::set<typename SequenceContainer::value_type> s;
    for( auto& i : seq) s.insert(i);
    
    if(s.size() != seq.size() )
        throw std::invalid_argument("Not a unique range");

    seq.assign(s.begin(), s.end());
}

// Prepares a 2D matrix of unsigned integers such that for any two values
// pref[2][3] and pref[2][4] signify that preferer[2] prefers preferee[pref[2][3]]
// to preferee[pref[2][4]]. Expects (n+1)*n tokens where n is the size of proposer
// and each n+1 token group is some preferer followed by n preferees.
template <typename RandomAccessContainer>
void populatePreferenceList(std::istream& in, 
			    typename RandomAccessContainer::size_type* pref,
			    RandomAccessContainer& preferer,
                            RandomAccessContainer& preferee )
{
    typename RandomAccessContainer::value_type name;
    auto n = preferer.size();
    for(decltype(n) i = 0; i < n; i++)
    {
	in >> name;
	auto itr = std::lower_bound(preferer.begin(), preferer.end(), name);
	auto idx =static_cast<decltype(n)>(itr - preferer.begin());

        for(decltype(n) j = 0; j < n; j++)
        {
            in >> name;
            itr = std::lower_bound(preferee.begin(), preferee.end(), name);
            pref[idx * n + j] = static_cast<decltype(n)>(itr - preferee.begin());
        }
    }
}

// Given p which contains preference lists, prepares r such that
// r[i][j] is the rank i gives j between (0, n).
template<typename T>
void calculateRankings(T* r, T* p,T n)
{
    for(decltype(n) i = 0; i < n; i++)
    {
	for(decltype(n) j = 0; j < n; j++)
	{
	    r[n*i + p[n*i + j] ]= j;
	}
    }
}
