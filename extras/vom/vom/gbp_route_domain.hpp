/*
 * Copyright (c) 2017 Cisco and/or its affiliates.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __VOM_GBP_ROUTE_DOMAIN_H__
#define __VOM_GBP_ROUTE_DOMAIN_H__

#include "vom/interface.hpp"
#include "vom/route_domain.hpp"
#include "vom/singular_db.hpp"
#include "vom/types.hpp"

namespace VOM {

/**
 * A entry in the ARP termination table of a Route Domain
 */
class gbp_route_domain : public object_base
{
public:
  /**
   * The key for a route_domain is the pari of EPG-IDs
   */
  typedef route_domain::key_t key_t;

  /**
   * Construct a GBP route_domain
   */
  gbp_route_domain(const route_domain& rd);

  gbp_route_domain(const route_domain& rd,
                   const interface& ip4_uu_fwd,
                   const interface& ip6_uu_fwd);
  gbp_route_domain(const route_domain& rd,
                   const std::shared_ptr<interface> ip4_uu_fwd,
                   const std::shared_ptr<interface> ip6_uu_fwd);

  /**
   * Copy Construct
   */
  gbp_route_domain(const gbp_route_domain& r);

  /**
   * Destructor
   */
  ~gbp_route_domain();

  /**
   * Return the object's key
   */
  const key_t key() const;

  /**
   * Return the route domain's VPP ID
   */
  route::table_id_t id() const;

  /**
   * comparison operator
   */
  bool operator==(const gbp_route_domain& rdae) const;

  /**
   * Return the matching 'singular instance'
   */
  std::shared_ptr<gbp_route_domain> singular() const;

  /**
   * Find the instnace of the route_domain domain in the OM
   */
  static std::shared_ptr<gbp_route_domain> find(const key_t& k);

  /**
   * Dump all route_domain-doamin into the stream provided
   */
  static void dump(std::ostream& os);

  /**
   * replay the object to create it in hardware
   */
  void replay(void);

  /**
   * Convert to string for debugging
   */
  std::string to_string() const;

  /**
   * Accessors for children
   */
  const std::shared_ptr<route_domain> get_route_domain() const;
  const std::shared_ptr<interface> get_ip4_uu_fwd() const;
  const std::shared_ptr<interface> get_ip6_uu_fwd() const;

private:
  /**
   * Class definition for listeners to OM events
   */
  class event_handler : public OM::listener, public inspect::command_handler
  {
  public:
    event_handler();
    virtual ~event_handler() = default;

    /**
     * Handle a populate event
     */
    void handle_populate(const client_db::key_t& key);

    /**
     * Handle a replay event
     */
    void handle_replay();

    /**
     * Show the object in the Singular DB
     */
    void show(std::ostream& os);

    /**
     * Get the sortable Id of the listener
     */
    dependency_t order() const;
  };

  /**
   * event_handler to register with OM
   */
  static event_handler m_evh;

  /**
   * Commit the acculmulated changes into VPP. i.e. to a 'HW" write.
   */
  void update(const gbp_route_domain& obj);

  /**
   * Find or add the instance of the route_domain domain in the OM
   */
  static std::shared_ptr<gbp_route_domain> find_or_add(
    const gbp_route_domain& temp);

  /*
   * It's the VPPHW class that updates the objects in HW
   */
  friend class OM;

  /**
   * It's the singular_db class that calls replay()
   */
  friend class singular_db<key_t, gbp_route_domain>;

  /**
   * Sweep/reap the object if still stale
   */
  void sweep(void);

  /**
   * HW configuration for the result of creating the endpoint
   */
  HW::item<uint32_t> m_id;

  std::shared_ptr<route_domain> m_rd;
  std::shared_ptr<interface> m_ip4_uu_fwd;
  std::shared_ptr<interface> m_ip6_uu_fwd;

  /**
   * A map of all route_domains
   */
  static singular_db<key_t, gbp_route_domain> m_db;
};

}; // namespace

/*
 * fd.io coding-style-patch-verification: ON
 *
 * Local Variables:
 * eval: (c-set-style "mozilla")
 * End:
 */

#endif
