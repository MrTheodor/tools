/*
 *            Copyright 2009-2018 The VOTCA Development Team
 *                       (http://www.votca.org)
 *
 *      Licensed under the Apache License, Version 2.0 (the "License")
 *
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <votca/tools/graphdistvisitor.h>
#include <votca/tools/graphnode.h>
#include <votca/tools/graph.h>
#include <votca/tools/edge.h>

using namespace std;

namespace votca {
namespace tools {

bool GraphDistVisitor::queEmpty(){
  return edge_que_.empty(); 
}

// Add the distance to the node that has not yet been explored
void GraphDistVisitor::exploreNode_(pair<int,GraphNode&> p_gn,Graph g, Edge ed){
  // Determine if the node has already been explored
  int vertex = p_gn.first;
  if(vertex==startingVertex_){
    GraphNode gn = p_gn.second;
    p_gn.second.int_vals_["Dist"] = 0;
  }else{
    // Node has not been explored
    if(explored_.count(vertex)==0){ 
      int prev_vertex = ed.getOtherV(vertex);
      GraphNode gn_prev = g.getNode(prev_vertex); 
      p_gn.second.int_vals_["Dist"]=gn_prev.int_vals_["Dist"]+1;
    }
  }
}

Edge GraphDistVisitor::getEdge_(Graph g){
  Edge ed = edge_que_.at(0).front();
  edge_que_.at(0).pop();
  if(edge_que_.at(0).size()==0){
    edge_que_.pop_front();
  }
}

// Add edges to be explored
void GraphDistVisitor::addEdges_(Graph g, int vertex){
  auto eds = g.getNeighEdges(vertex);
  // Proceed to add them to queue if the vertices
  // they refer to are not already explored
 
  // If first edges to be added
  if(edge_que_.empty()){
    queue<Edge> first_que;
    for(auto ed : eds ){
      first_que.push(ed);
    }
    edge_que_.push_back(first_que);
  }else{

    if(edge_que_.size()==1){
      queue<Edge> next_que;
      for(auto ed : eds ){
        int neigh_vert = ed.getOtherV(vertex);
        if(explored_.count(neigh_vert)==0){
          next_que.push(ed);
        }
      }
      edge_que_.push_back(next_que);
    }else{
      for(auto ed : eds ){
        int neigh_vert = ed.getOtherV(vertex);
        if(explored_.count(neigh_vert)==0){
          // Add the edges to the next highest distance queue    
          edge_que_.at(1).push(ed);
        }
      }
    }
  }
}

}
}
