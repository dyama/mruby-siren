##
#
# Siren module
#

module Siren

  extend Build
  extend Heal
  extend Offset
  extend Prim
  include Build
  include Heal
  include Offset
  include Prim

  def self.warn(*msg)
    return if $VERBOSE.nil? && msg.empty?
    $stderr.puts("siren: warning: " + msg.join)
  end

end

