class FixColumnName < ActiveRecord::Migration
  def self.up
    rename_column :events, :where, :location
  end

  def self.down
  end
end
