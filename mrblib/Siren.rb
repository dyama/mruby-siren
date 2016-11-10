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
      c = BSCurve.new(*args)
    else
      c = BSCurve.new(*(args[0..4]))
    end
    if args.size == 7 # with limit paramters
      Edge.new c, args[5], args[6]
    else
      Edge.new c
    end
  end

  def bscurve(*args)
    Siren.bscurve(*args)
  end

  def self.bzcurve(*args)
    c = nil
    if args.size <= 2
      c = BzCurve.new(*args)
    else
      c = BzCurve.new(*(args[0..1]))
    end
    if args.size == 4 # with limit parameters
      Edge.new c, args[-2], args[-1]
    else
      Edge.new c
    end
  end

  def bzcurve(*args)
    Siren.bzcurve(*args)
  end

  # Alias
  {
    Siren::Vertex => {
      :vertex     => :new
    },
    Siren::Wire => {
      :wire       => :make,
    },
    Siren::Face => {
      :plane      => :plane,
      :face       => :face,
      :infplane   => :infplane,
      :polygon    => :polygon,
      :bzsurf     => :bzsurf,
      :bssurf     => :bssurf,
    },
    Siren::Shell => {
      :sew        => :make,
      :shell      => :make,
    },
    Siren::Solid => {
      :box        => :box,
      :box2p      => :box2p,
      :boxax      => :boxax,
      :sphere     => :sphere,
      :cylinder   => :cylinder,
      :cone       => :cone,
      :torus      => :torus,
      :halfspace  => :halfspace,
      :prism      => :prism,
      :revol      => :revol,
      :revolution => :revolution,
      :wedge      => :wedge,
    }
  }.each do |c, ms|
    ms.each do |ma, mo|
      # ma = Alias method name
      # mo = Original method name
      # puts "Export #{c}.#{mo} as Siren.#{ma}"
      self.define_singleton_method(ma) do |*args|
        c.send(mo, *args)
      end
      self.class_eval do
        self.define_method(ma) do |*args|
          c.send(mo, *args)
        end
      end
    end
  end

end

