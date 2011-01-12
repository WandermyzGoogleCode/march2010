class CreateInvitations < ActiveRecord::Migration
  def self.up
    create_table :invitations do |t|
      t.integer :event_id
      t.text :extra_info

      t.timestamps
    end
  end

  def self.down
    drop_table :invitations
  end
end
