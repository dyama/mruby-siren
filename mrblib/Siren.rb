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

  def self.bscurve(*args)
    c = nil
    if args.size == 4
      c = BSCurve.new *args
    else
      c = BSCurve.new *(args[0..4])
    end
    if args.size == 7 # with limit paramters
      Edge.new c, args[5], args[6]
    else
      Edge.new c
    end
  end

  def bscurve(*args)
    Siren.bscurve *args
  end

  def self.bzcurve(*args)
    c = nil
    if args.size <= 2
      c = BzCurve.new *args
    else
      c = BzCurve.new *(args[0..1])
    end
    if args.size == 4 # with limit parameters
      Edge.new c, args[-2], args[-1]
    else
      Edge.new c
    end
  end

  def bzcurve(*args)
    Siren.bzcurve *args
  end

  def self.vertex(*args)
    if args.size == 0
      Siren::Vertex.new
    else
      Siren::Vertex.new *args
    end
  end

  def vertex(*args)
    Siren.vertex *args
  end

  def self.compound(*args)
    Compound.new *args
  end

  def compound(*args)
    Siren.compound *args
  end

end

