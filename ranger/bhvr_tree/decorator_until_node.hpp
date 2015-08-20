// Copyright (c) 2015, RangerUFO
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
// 
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
// 
// * Neither the name of ranger_bhvr_tree nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef RANGER_BHVR_TREE_DECORATOR_UNTIL_NODE_HPP
#define RANGER_BHVR_TREE_DECORATOR_UNTIL_NODE_HPP

#include "ranger/bhvr_tree/abstract_node.hpp"

namespace ranger { namespace bhvr_tree {

template <class AgentProxy>
class decorator_until_node : public abstract_node<AgentProxy> {
public:
	decorator_until_node(bool result) : m_result(result) {
		// nop
	}

	void exec(AgentProxy& ap, std::function<void(bool)> hdl) const final {
		auto node = this->get_first_child();
		if (node) {
			exec_impl(ap, node, std::move(hdl));
		} else {
			hdl(false);
		}
	}

private:
	void exec_impl(	AgentProxy& ap,
					abstract_node<AgentProxy>* node,
					std::function<void(bool)> hdl) const {
		node->exec(ap, [=, &ap] (bool result) {
			if (result == m_result) {
				hdl(result);
			} else {
				exec_impl(ap, node, std::move(hdl));
			}
		});
	}

	bool m_result;
};

} }

#endif	// RANGER_BHVR_TREE_DECORATOR_UNTIL_NODE_HPP