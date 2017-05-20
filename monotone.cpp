// O(N log N) Monotone Chains algorithm for 2d convex hull.
// Implementation by Brian Bi.
// Gives the hull in counterclockwise order from the leftmost point, which is repeated at the end. Minimizes the number of points on the hull when collinear points exist.
long long cross(pair<int, int> A, pair<int, int> B, pair<int, int> C) {
	return (B.first - A.first)*(C.second - A.second)
	     - (B.second - A.second)*(C.first - A.first);
}
// The hull is returned in param "hull"
void convex_hull(vector<pair<int, int> > pts, vector<pair<int, int> >& hull) {
	hull.clear(); sort(pts.begin(), pts.end());
	for (int i = 0; i < pts.size(); i++) {
		while (hull.size() >= 2 && cross(hull[hull.size()-2], hull.back(), pts[i]) <= 0) {
			hull.pop_back();
		}
		hull.push_back(pts[i]);
	}
	int s = hull.size();
	for (int i = pts.size()-2; i >= 0; i--) {
		while (hull.size() >= s+1 && cross(hull[hull.size()-2], hull.back(), pts[i]) <= 0) {
			hull.pop_back();
		}
		hull.push_back(pts[i]);
	}
}

// O(N log N) Grahm's scan algorithm for 2d convex hull.
// Python implementation on Leetcode Q587
// First select a pivot point s0 to be the one with smallest y (smallest x as tiebreaker)
// Then sort all points in increasing order of phi
class ConvexHullSolution:
	def CH(self, points):
        # Computes the cross product of vectors p1p2 and p2p3
        # value of 0 means points are colinear; < 0, cw; > 0, ccw
        def cross(p1, p2, p3):
            return (p2.x - p1.x)*(p3.y - p1.y) - (p2.y - p1.y)*(p3.x - p1.x)

        # Computes slope of line between p1 and p2
        def slope(p1, p2):
            return 1.0*(p1.y-p2.y)/(p1.x-p2.x) if p1.x != p2.x else float('inf')

        # Find the smallest left point and remove it from points
        start = min(points, key=lambda p: (p.x, p.y))
        points.pop(points.index(start))

        # Sort points so that traversal is from start in a ccw circle.
        points.sort(key=lambda p: (slope(p, start), -p.y, p.x))

        # Add each point to the convex hull.
        # If the last 3 points make a cw turn, the second to last point is not in CH.
        ans = [start]
        for p in points:
            ans.append(p)
            while len(ans) > 2 and cross(ans[-3], ans[-2], ans[-1]) < 0:
                ans.pop(-2)

        return ans
