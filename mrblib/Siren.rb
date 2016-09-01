##
#
# Siren module
#

module Siren

  extend Build
  extend Heal
  extend Offset
  include Build
  include Heal
  include Offset

  def self.warn(*msg)
    return if $VERBOSE.nil? && msg.empty?
    $stderr.puts("siren: warning: " + msg.join)
  end

  def self.save_model(shape, path)
    e5 = path[-5, path.size].downcase
    e4 = path[-4, path.size].downcase
    if e5 == ".brep" || e4 == ".brp"
      Siren.save_brep shape, path
    elsif e5 == ".iges" || e4 == ".igs"
      Siren.save_iges shape, path
    elsif e5 == ".step" || e4 == ".stp"
      Siren.save_step shape, path
    elsif e4 == ".stl"
      Siren.save_stl shape, path
    else
      raise TypeError
    end
  end

  def save_model(shape, path)
    Siren.save_model(shape, path)
  end

end

