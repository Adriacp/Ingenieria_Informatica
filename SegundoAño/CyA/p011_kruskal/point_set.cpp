#include <iostream>
#include <algorithm>

#include "point_set.hpp"
#include "point_types.hpp"
#include "sub_tree.hpp"

    void point_set::EMST(void)
    {
        CyA::arc_vector av;
        compute_arc_vector(av);

        forest st;

        for (const CyA::point &p : *this)
        {
            EMST::sub_tree s;
            s.add_point(p);

            st.push_back(s);
        }

        for (const CyA::weigthed_arc &a : av)
        {
            int i, j;
            find_incident_subtrees(st, a.second, i, j);

            if (i != j)
            {
                merge_subtrees(st, a.second, i, j);
            }
        }

        emst_ = st[0].get_arcs();
    }

    void point_set::compute_arc_vector(CyA::arc_vector &av) const
    {
        av.clear();
 
        const int n = size();
 
        for (int i = 0; i < n - 1; ++i)
        {
            const CyA::point &p_i = (*this)[i];
 
            for (int j = i + 1; j < n; ++j)
            {
                const CyA::point &p_j = (*this)[j];
 
                const double dist = euclidean_distance(std::make_pair(p_i, p_j));
 
                av.push_back(std::make_pair(dist, std::make_pair(p_i, p_j)));
            }
        }
 
        std::sort(av.begin(), av.end());
    }