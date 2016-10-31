##
#
# Siren module
#

module Siren

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
    elsif e4 == ".ply"
      Siren.save_ply shape, path
    elsif e4 == ".dxf"
      Siren.save_dxf shape, path
    elsif e4 == ".dat"
      Siren.save_plot shape, path
    else
      raise TypeError
    end
  end

  def save_model(shape, path)
    Siren.save_model(shape, path)
  end

  def self.load_model(path)
    e5 = path[-5, path.size].downcase
    e4 = path[-4, path.size].downcase
    if e5 == ".brep" || e4 == ".brp"
      Siren.load_brep path
    elsif e5 == ".iges" || e4 == ".igs"
      Siren.load_iges path
    elsif e5 == ".step" || e4 == ".stp"
      Siren.load_step path
    elsif e4 == ".stl"
      Siren.load_stl path
    else
      raise TypeError
    end
  end

  def load_model(path)
    Siren.load_model(path)
  end

  def self.nurbscurve(*args)
    c = nil
    if args.size == 4
      c = BSplineCurve.new *args
    else
      c = BSplineCurve.new *(args[0..4])
    end
    if args.size == 7
      Siren.curve c, args[5], args[6]
    else
      Siren.curve c
    end
  end

  def nurbscurve(*args)
    Siren.nurbscurve *args
  end

end

