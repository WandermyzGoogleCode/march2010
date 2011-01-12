class CreateRecommendations < ActiveRecord::Migration
  def self.up
    create_table :recommendations do |t|
      t.integer :event_id
      t.integer :group_id
      t.integer :admin_id
      t.text :extra_info
      t.integer :timestamp

      t.timestamps
    end
  end

  def self.down
    drop_table :recommendations
  end
end
