class AddTimestampToInvitation < ActiveRecord::Migration
  def self.up
    add_column :invitations, :timestamp, :integer
  end

  def self.down
    remove_column :invitations, :timestamp
  end
end
